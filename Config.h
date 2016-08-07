//
// Created by tim on 05.08.16.
//

#ifndef ESCAPE_THE_TROLLS_CONFIG_H
#define ESCAPE_THE_TROLLS_CONFIG_H

#define TILE_SIZE 50
#define PLAYER_SIZE 40
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define MAP_SIZE (73 * 23)

struct Tile;

struct Map {
    Tile *tiles;
    int w;
    int h;
} typedef Map;

struct Tile {
    int type;
    int absoluteNumber;
    int posX;
    int posY;
};

#endif //ESCAPE_THE_TROLLS_CONFIG_H
