#include <iostream>
#include <fstream>
#include "SDLWrapper.h"

void loadAllTextures(SDLWrapper *SDL);

Map *loadMap();

int main() {

    SDLWrapper *SDL = new SDLWrapper(SDL_INIT_VIDEO);
    SDL->createWindow("Escape the Trolls", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    loadAllTextures(SDL);

    SDL->generateMap(5, 5);

    return 1;

    Map *map = loadMap();
    SDL->assignMap(map);
    MoveableObject *player = SDL->createPlayer();

    SDL_Rect camRect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    Camera camera(camRect);
    SDL->setCamera(&camera);

    TTF_Init();

    TTF_Font *Sans = TTF_OpenFont("fonts/OpenSans-Regular.ttf", 25);
    if (Sans == nullptr) {
        std::cout << "Unable to load OpenSans-Regular.ttf" << "Error: " << TTF_GetError() << std::endl;
        exit(1);
    }
    unsigned int numTurns = 0;
    std::string numTurnsString = std::to_string(numTurns);
    TextObject *roundText = SDL->createTextObject("Rounds: " + numTurnsString, 0, 0, 0, 0, Sans,
                                                  SDL_Color {255, 255, 255});


    bool nextTurn = false;

    SDL->update();
    while (SDL->isRunning()) {
        unsigned int e = SDL->eventPoll();
        if (e == SDL_QUIT) {
            SDL->stopRunning();
        } else {
            switch (e) {
                case Up:
                    nextTurn = player->move(MoveableObject::Up, map);
                    break;
                case Down:
                    nextTurn = player->move(MoveableObject::Down, map);
                    break;
                case Left:
                    nextTurn = player->move(MoveableObject::Left, map);
                    break;
                case Right:
                    nextTurn = player->move(MoveableObject::Right, map);
                    break;
                case Push: {
                    std::pair<int, int> tiles = player->push(map);
                    SDL->updateMap(tiles);
                    nextTurn = true;
                    break;
                }
                default:
                    break;
            }
        }
        if (nextTurn) {
            numTurns++;
            numTurnsString = std::to_string(numTurns);
            roundText->setText("Rounds: " + numTurnsString);
            nextTurn = false;
            SDL->update();
        }
        SDL->render();
    }

    TTF_CloseFont(Sans);

    return 0;
}

void loadAllTextures(SDLWrapper *SDL) {
    SDL->loadTexture("wall", "textures/rock_texture.png");
    SDL->loadTexture("player", "textures/shape_triangle.png");
}

Map *loadMap() {
    std::ifstream map_file;
    map_file.open("maps/level1.dat");

    int map_size = 0;
    int num_rows = 0;
    int num_cols = 0;
    if (map_file.is_open()) {
        char c;
        while (map_file.get(c)) {
            if (c == '\n') {
                num_rows++;
                continue;
            } else {
                map_size++;
            }
        }
    }
    map_file.close();
    num_cols = map_size / num_rows;

    Tile *map_values = new Tile[map_size];

    Map *map = new Map{map_values, num_cols, num_rows};

    map_file.open("maps/level1.dat");

    if (map_file.is_open()) {
        char c;
        int i = 0;
        while (map_file.get(c)) {
            if (c == '\n') {
                continue;
            } else {
                if (c == '#') {
                    map_values[i].type = 1;
                } else if (c == ' ') {
                    map_values[i].type = 0;
                } else if (c == 'X') {
                    map_values[i].type = 2;
                }
                map_values[i].tileNumber = i;
                map_values[i].posX = i % num_cols;
                map_values[i].posY = i / num_cols;
            }
            i++;
        }
    }

    return map;
}























