//
// Created by tim on 05.08.16.
//

#ifndef ESCAPE_THE_TROLLS_DRAWABLEOBJECT_H
#define ESCAPE_THE_TROLLS_DRAWABLEOBJECT_H

#include <string>
#include <SDL.h>
#include "Camera.h"
#include "Enumerations.h"

class DrawableObject {

public:
    DrawableObject();

    DrawableObject(SDL_Texture *texture, int x, int y, int w, int h, DrawableTypes tag, int id);

    virtual void render(SDL_Renderer *renderer, Camera camera);

    virtual void update();

protected:
    SDL_Point calculateTilePosition() const;

public:
    SDL_Texture *mTexture;
    SDL_Rect mBoundingBox;
    SDL_Rect mTextureRect;
    double angle = 0;
    DrawableTypes mTag;
    int mId;

};


#endif //ESCAPE_THE_TROLLS_DRAWABLEOBJECT_H
