//
// Created by tim on 06.08.16.
//

#include "Camera.h"

Camera::Camera(SDL_Rect boundingBox) {
    mBoundingBox = boundingBox;
}

void Camera::setPosition(int x, int y) {
    mBoundingBox.x = x;
    mBoundingBox.y = y;
}

SDL_Point Camera::getPosition() const {
    return SDL_Point{mBoundingBox.x, mBoundingBox.y};
}
