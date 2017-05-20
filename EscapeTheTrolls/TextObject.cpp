//
// Created by tim on 05.08.16.
//

#include "TextObject.h"

TextObject::TextObject(SDL_Texture *texture, int x, int y, int w, int h, TTF_Font *font, DrawableTypes tag) :
        DrawableObject(texture, x, y, w, h, tag, 0) {
    mFont = font;
}

void TextObject::setColor(Uint8 r, Uint8 g, Uint8 b) {
    mColor = SDL_Color {r, g, b};
}

void TextObject::setText(std::string text) {

    mText = text;

}

void TextObject::update(SDL_Renderer *renderer) {
    SDL_Surface *surface = TTF_RenderText_Solid(mFont, mText.c_str(), mColor);
    mTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(mTexture, nullptr, nullptr, &mTextureRect.w, &mTextureRect.h);
    SDL_QueryTexture(mTexture, nullptr, nullptr, &mBoundingBox.w, &mBoundingBox.h);
    SDL_FreeSurface(surface);
    DrawableObject::update();
}

void TextObject::render(SDL_Renderer *renderer, Camera camera) {
    if (mTag == StaticText) {
        SDL_RenderCopyEx(renderer, mTexture, &mTextureRect, &mBoundingBox, angle, nullptr, SDL_FLIP_NONE);
    } else {
        DrawableObject::render(renderer, camera);
    }
}

