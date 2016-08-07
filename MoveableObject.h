//
// Created by tim on 05.08.16.
//

#ifndef ESCAPE_THE_TROLLS_MOVEABLEOBJECT_H
#define ESCAPE_THE_TROLLS_MOVEABLEOBJECT_H


#include "DrawableObject.h"
#include "Enumerations.h"
#include "Config.h"

class MoveableObject : public DrawableObject {

public:
    enum Direction {
        None,
        Up,
        Down,
        Left,
        Right
    };

public:
    MoveableObject(SDL_Texture *texture, int x, int y, int w, int h, DrawableTypes tag, int id);

    void setPosition(int x, int y);

    bool move(MoveableObject::Direction direction, Map *map);

    virtual void update();

    bool isPossibleMove(Map *map, MoveableObject::Direction direction, int i);

    std::pair<int, int> push(Map *map);

private:

    void turn(MoveableObject::Direction direction);

    void setMovement(MoveableObject::Direction direction);

private:
    int mNextMoveX = 0;
    int mNextMoveY = 0;
    Direction mDirection = Up;

};


#endif //ESCAPE_THE_TROLLS_MOVEABLEOBJECT_H
