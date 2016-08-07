//
// Created by tim on 06.08.16.
//

#ifndef ESCAPE_THE_TROLLS_CAMERA_H
#define ESCAPE_THE_TROLLS_CAMERA_H


#include <SDL_rect.h>

class Camera {

public:
    Camera(SDL_Rect boundingBox);

    SDL_Point getPosition() const;

    void setPosition(int x, int y);

private:

    SDL_Rect mBoundingBox;
};


#endif //ESCAPE_THE_TROLLS_CAMERA_H
