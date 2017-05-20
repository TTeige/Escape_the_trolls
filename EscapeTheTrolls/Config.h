//
// Created by tim on 05.08.16.
//

#ifndef ESCAPE_THE_TROLLS_CONFIG_H
#define ESCAPE_THE_TROLLS_CONFIG_H

#define TILE_SIZE 50
#define PLAYER_SIZE 40
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define MAP_SIZE_WIDTH 73
#define MAP_SIZE_HEIGHT 23

struct Tile;
struct GenerationTiles;

struct GenerationMap {
    GenerationTiles *tiles;
    int w;
    int h;
};

struct GenerationTiles {
    int posX = -1;
    int posY = -1;
    int absoluteNumber = -1;
    int generationInformation[5]{0, 0, 0, 0, 0};
};

struct Map {
    Tile *tiles;
    int w;
    int h;
} typedef Map;

struct Tile {
    int type;
    int tileNumber;
    int posX;
    int posY;
};

#endif //ESCAPE_THE_TROLLS_CONFIG_H
