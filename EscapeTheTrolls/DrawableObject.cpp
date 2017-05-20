//
// Created by tim on 05.08.16.
//

#include "DrawableObject.h"
#include "Config.h"

DrawableObject::DrawableObject() {

}

DrawableObject::DrawableObject(SDL_Texture *texture, int x, int y, int w, int h, DrawableTypes tag, int id) {

    mId = id;
    mTag = tag;
    mTexture = texture;
    mTextureRect.x = 0;
    mTextureRect.y = 0;
    SDL_QueryTexture(mTexture, nullptr, nullptr, &mTextureRect.w, &mTextureRect.h);
    mBoundingBox.x = x;
    mBoundingBox.y = y;
    mBoundingBox.w = w;
    mBoundingBox.h = h;
}

void DrawableObject::render(SDL_Renderer *renderer, Camera camera) {

    SDL_Point pos = camera.getPosition();
    SDL_Rect tmp = mBoundingBox;
    tmp.x -= pos.x;
    tmp.y -= pos.y;
    SDL_RenderCopyEx(renderer, mTexture, &mTextureRect, &tmp, angle, nullptr, SDL_FLIP_NONE);

}

void DrawableObject::update() {

}

SDL_Point DrawableObject::calculateTilePosition() const {
    return SDL_Point{mBoundingBox.x / TILE_SIZE, mBoundingBox.y / TILE_SIZE};
}

