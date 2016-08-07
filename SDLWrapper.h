//
// Created by tim on 05.08.16.
//

#ifndef ESCAPE_THE_TROLLS_SDLWRAPPER_H
#define ESCAPE_THE_TROLLS_SDLWRAPPER_H

#include <SDL.h>
#include <vector>
#include <map>
#include <string>
#include <SDL_ttf.h>
#include "DrawableObject.h"
#include "Enumerations.h"
#include "MoveableObject.h"
#include "TextObject.h"
#include "Config.h"

class SDLWrapper {

public:
    SDLWrapper(unsigned int flags);

    virtual ~SDLWrapper();

    void createWindow(const char *title, int w, int h, unsigned int flags);

    void destroyWindow();

    void createRenderer();

    void destroyRenderer();

    void loadTexture(std::string name, const char *path);

    void clearTextures();

    unsigned int eventPoll();

    void assignMap(Map *map);

    void clearMap();

    void update();

    void render();

    void setCamera(Camera *camera);

    void addDrawableObject(std::string textureName, int x, int y, int width, int height, DrawableTypes tag, int id);

    void addMovableObject(std::string textureName, int x, int y, int width, int height, DrawableTypes tag);

    MoveableObject *createPlayer();

    TextObject *createTextObject(std::string originalText, int x, int y, int w, int h,
                                 TTF_Font *font, SDL_Color color);

    void updateMap(std::pair<int, int> changedTiles);

private:

    void sdlPrintError();

    void freeDrawableObjects();

    void freeTextObjects();

    bool isOutofBounds(int changedTile) const;

private:
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;

    SDL_Event mEvent;

    Camera *mCamera;

    std::map<std::string, SDL_Texture *> mTextures;
    std::vector<DrawableObject *> mDrawableObjects;
    std::vector<TextObject *> mTextObjects;

    Map *mStoredMap;

    unsigned int mObjectIdTracker = 0;

};


#endif //ESCAPE_THE_TROLLS_SDLWRAPPER_H
