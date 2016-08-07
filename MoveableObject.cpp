//
// Created by tim on 05.08.16.
//

#include "MoveableObject.h"

MoveableObject::MoveableObject(SDL_Texture *texture, int x, int y, int w, int h, DrawableTypes tag, int id)
        : DrawableObject(
        texture, x, y, w, h, tag, id) {
}

void MoveableObject::setPosition(int x, int y) {
    mBoundingBox.x = x;
    mBoundingBox.y = y;
}

bool MoveableObject::move(MoveableObject::Direction direction, Map *map) {
    bool hasMoved = false;
    if (mDirection != direction) {
        turn(direction);
        hasMoved = true;
    } else if (isPossibleMove(map, direction, 1)) {
        setMovement(direction);
        hasMoved = true;
    }
    return hasMoved;
}

void MoveableObject::update() {

    mBoundingBox.x += mNextMoveX;
    mBoundingBox.y += mNextMoveY;
    mNextMoveX = 0;
    mNextMoveY = 0;

}

void MoveableObject::turn(MoveableObject::Direction direction) {
    switch (direction) {
        case MoveableObject::Up:
            angle = 0;
            break;
        case MoveableObject::Down:
            angle = 180;
            break;
        case MoveableObject::Left:
            angle = 270;
            break;
        case MoveableObject::Right:
            angle = 90;
            break;
        default:
            angle = 0;
            break;
    }
    mDirection = direction;
}

void MoveableObject::setMovement(MoveableObject::Direction direction) {
    switch (direction) {
        case MoveableObject::Up:
            mNextMoveY -= TILE_SIZE;
            break;
        case MoveableObject::Down:
            mNextMoveY += TILE_SIZE;
            break;
        case MoveableObject::Left:
            mNextMoveX -= TILE_SIZE;
            break;
        case MoveableObject::Right:
            mNextMoveX += TILE_SIZE;
            break;
        default:
            break;
    }
}

bool MoveableObject::isPossibleMove(Map *map, MoveableObject::Direction direction, int i) {
    SDL_Point tilePos = calculateTilePosition();
    bool possibleMove = true;
    switch (direction) {
        case MoveableObject::Up:
            possibleMove = map->tiles[map->w * (tilePos.y - i) + tilePos.x].type != 1;
            break;
        case MoveableObject::Down:
            possibleMove = map->tiles[map->w * (tilePos.y + i) + tilePos.x].type != 1;
            break;
        case MoveableObject::Left:
            possibleMove = map->tiles[map->w * tilePos.y + (tilePos.x - i)].type != 1;
            break;
        case MoveableObject::Right:
            possibleMove = map->tiles[map->w * tilePos.y + (tilePos.x + i)].type != 1;
            break;
        default:
            break;
    }
    return possibleMove;
}

std::pair<int, int> MoveableObject::push(Map *map) {
    std::pair<int, int> changedTiles;
    if (isPossibleMove(map, mDirection, 2)) {
        SDL_Point tilePos = calculateTilePosition();
        switch (mDirection) {
            case MoveableObject::Up:
                changedTiles.first = map->w * (tilePos.y - 1) + tilePos.x;
                changedTiles.second = map->w * (tilePos.y - 2) + tilePos.x;
                break;
            case MoveableObject::Down:
                changedTiles.first = map->w * (tilePos.y + 1) + tilePos.x;
                changedTiles.second = map->w * (tilePos.y + 2) + tilePos.x;
                break;
            case MoveableObject::Left:
                changedTiles.first = map->w * tilePos.y + tilePos.x - 1;
                changedTiles.second = map->w * tilePos.y + tilePos.x - 2;
                break;
            case MoveableObject::Right:
                changedTiles.first = map->w * tilePos.y + tilePos.x + 1;
                changedTiles.second = map->w * tilePos.y + tilePos.x + 2;
                break;
            default:
                break;
        }
    }
    return changedTiles;
}

bool MoveableObject::isAtEnd(Map *map) const {
    SDL_Point tilePos = calculateTilePosition();
    return map->tiles[map->w * tilePos.y + tilePos.x].type == 2;
}























