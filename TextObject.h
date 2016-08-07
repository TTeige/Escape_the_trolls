//
// Created by tim on 05.08.16.
//

#ifndef ESCAPE_THE_TROLLS_TEXTOBJECT_H
#define ESCAPE_THE_TROLLS_TEXTOBJECT_H


#include <SDL_ttf.h>
#include "DrawableObject.h"

class TextObject : public DrawableObject {

public:
    TextObject(SDL_Texture *texture, int x, int y, int w, int h, TTF_Font *font, DrawableTypes tag);

    void setText(std::string text);

    void setColor(Uint8 r, Uint8 b, Uint8 g);

    virtual void render(SDL_Renderer *renderer, Camera camera);

    void update(SDL_Renderer *renderer);

private:
    std::string mText;
    SDL_Color mColor{255, 255, 255};
    TTF_Font *mFont;
};


#endif //ESCAPE_THE_TROLLS_TEXTOBJECT_H
