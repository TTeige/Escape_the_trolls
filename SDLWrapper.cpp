//
// Created by tim on 05.08.16.
//

#include <iostream>
#include <SDL_image.h>
#include "SDLWrapper.h"

SDLWrapper::SDLWrapper(unsigned int flags) {
    SDL_Init(flags);
    mIsRunning = true;
}

SDLWrapper::~SDLWrapper() {
    destroyWindow();
    destroyRenderer();
    clearTextures();
    clearMap();
    freeDrawableObjects();
    freeTextObjects();
    SDL_Quit();
    TTF_Quit();
}

void SDLWrapper::createWindow(const char *title, int w, int h, unsigned int flags) {
    mWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);
    if (mWindow == NULL) {
        sdlPrintError();
    }

    createRenderer();
}

void SDLWrapper::sdlPrintError() {
    std::cout << "SDL Error caused at " << __LINE__ << "\t:" << SDL_GetError() << std::endl;
}

void SDLWrapper::destroyWindow() {
    if (mWindow != NULL) {
        SDL_DestroyWindow(mWindow);
    } else {
        std::cout << "Window not initialized, no need to destroy it" << std::endl;
    }
}

void SDLWrapper::createRenderer() {
    if (mWindow != NULL) {
        mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
    }

}

void SDLWrapper::destroyRenderer() {
    if (mRenderer != nullptr) {
        SDL_DestroyRenderer(mRenderer);
    } else {
        std::cout << "No renderer to destroy" << std::endl;
    }
}

unsigned int SDLWrapper::eventPoll() {
    if (SDL_PollEvent(&mEvent)) {
        if (mEvent.type == SDL_QUIT) {
            SDL_Quit();
            return SDL_QUIT;
        } else if (mEvent.type == SDL_KEYDOWN) {
            switch (mEvent.key.keysym.sym) {
                case SDLK_UP:
                    return Up;
                case SDLK_DOWN:
                    return Down;
                case SDLK_LEFT:
                    return Left;
                case SDLK_RIGHT:
                    return Right;
                case SDLK_SPACE:
                    return Push;
                default:
                    return None;
            }
        }
    }

    return None;
}

void SDLWrapper::loadTexture(std::string name, const char *path) {
    SDL_Surface *image = IMG_Load(path);
    if (image != nullptr) {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer, image);
        SDL_FreeSurface(image);
        mTextures.insert(std::pair<std::string, SDL_Texture *>(name, texture));
    } else {
        std::cout << "Unable to load texture: " << path << std::endl;
    }
}

void SDLWrapper::clearTextures() {
    for (auto &t : mTextures) {
        SDL_DestroyTexture(t.second);
    }
    mTextures.clear();
}

void SDLWrapper::render() {

    SDL_SetRenderDrawColor(mRenderer, 0x0, 0x0, 0x0, 0x0);
    SDL_RenderClear(mRenderer);
    for (auto &item : mDrawableObjects) {
        item->render(mRenderer, *mCamera);
    }
    for (auto &t : mTextObjects) {
        t->render(mRenderer, *mCamera);
    }
    SDL_RenderPresent(mRenderer);
}

void
SDLWrapper::addDrawableObject(std::string textureName, int x, int y, int width, int height, DrawableTypes tag, int id) {
    std::map<std::string, SDL_Texture *>::iterator it;
    it = mTextures.find(textureName);
    mDrawableObjects.push_back(new DrawableObject(it->second, x, y, width, height, tag, id));
}

void SDLWrapper::addMovableObject(std::string textureName, int x, int y, int width, int height, DrawableTypes tag) {
    std::map<std::string, SDL_Texture *>::iterator it;
    it = mTextures.find(textureName);
    mDrawableObjects.push_back(new MoveableObject(it->second, x, y, width, height, tag, mObjectIdTracker++));
}

TextObject *SDLWrapper::createTextObject(std::string originalText, int x, int y, int w, int h,
                                         TTF_Font *font, SDL_Color color) {

    SDL_Surface *surface = TTF_RenderText_Solid(font, originalText.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    TextObject *text = new TextObject(texture, x, y, w, h, font, StaticText);
    mTextObjects.push_back(text);
    return text;
}

MoveableObject *SDLWrapper::createPlayer() {
    std::map<std::string, SDL_Texture *>::iterator it;
    it = mTextures.find("player");
    MoveableObject *player = new MoveableObject(it->second, 0, 0, PLAYER_SIZE, PLAYER_SIZE, Player, mObjectIdTracker++);
    player->setPosition(TILE_SIZE, TILE_SIZE);
    mDrawableObjects.push_back(player);
    return player;
}

void SDLWrapper::update() {

    for (auto &m : mDrawableObjects) {
        m->update();
        if (m->mTag == Player) {
            mCamera->setPosition(m->mBoundingBox.x + (m->mBoundingBox.w / 2) - (SCREEN_WIDTH / 2),
                                 m->mBoundingBox.y + (m->mBoundingBox.h / 2) - (SCREEN_HEIGHT / 2));
            MoveableObject *player = static_cast<MoveableObject *>(m);
            if (player->isAtEnd(mStoredMap)) {
                stopRunning();
            }
        }
    }
    for (auto &t : mTextObjects) {
        t->update(mRenderer);
    }

}

void SDLWrapper::assignMap(Map *map) {
    mStoredMap = map;
    for (int i = 0; i < mStoredMap->w; i++) {
        for (int j = 0; j < mStoredMap->h; j++) {
            if (mStoredMap->tiles[mStoredMap->w * j + i].type == 1) {
                addDrawableObject("wall", i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE, Wall,
                                  mStoredMap->tiles[mStoredMap->w * j + i].absoluteNumber);
            }
        }
    }
}

void SDLWrapper::clearMap() {
    free(mStoredMap->tiles);
    free(mStoredMap);
}

void SDLWrapper::setCamera(Camera *camera) {

    mCamera = camera;

}

void SDLWrapper::freeDrawableObjects() {
    for (auto &m : mDrawableObjects) {
        free(m);
    }

}

void SDLWrapper::freeTextObjects() {
    for (auto &t : mTextObjects) {
        free(t);
    }
}

void SDLWrapper::updateMap(std::pair<int, int> changedTiles) {
    for (auto &obj : mDrawableObjects) {
        if (obj->mTag == Wall && (obj->mId == changedTiles.first)) {
            if (!isOutofBounds(changedTiles.second)) {
                mStoredMap->tiles[changedTiles.first].type = 0;
                mStoredMap->tiles[changedTiles.second].type = 1;
                obj->mBoundingBox.x = mStoredMap->tiles[changedTiles.second].posX * TILE_SIZE;
                obj->mBoundingBox.y = mStoredMap->tiles[changedTiles.second].posY * TILE_SIZE;
                obj->mId = mStoredMap->tiles[changedTiles.second].absoluteNumber;
                break;
            }
        }
    }


}

bool SDLWrapper::isOutofBounds(int changedTile) const {
    bool isOutofBounds = false;
    if (changedTile < 0 || changedTile > (mStoredMap->w * mStoredMap->h))
        isOutofBounds = true;
    if (mStoredMap->tiles[changedTile].posX < 0) {
        isOutofBounds = true;
    } else if (mStoredMap->tiles[changedTile].posX > mStoredMap->w) {
        isOutofBounds = true;
    } else if (mStoredMap->tiles[changedTile].posY < 0) {
        isOutofBounds = true;
    } else if (mStoredMap->tiles[changedTile].posY > mStoredMap->h) {
        isOutofBounds = true;
    }

    return isOutofBounds;
}

bool SDLWrapper::isRunning() {
    return mIsRunning;
}

void SDLWrapper::stopRunning() {
    mIsRunning = false;
}






































