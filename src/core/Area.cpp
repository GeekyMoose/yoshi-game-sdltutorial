#include "core/Area.h"

#include "helper/Logger.h"
#include "helper/gameConfig.h"

#if PLATFORM_WINDOWS
#   include <SDL.h>
#elif PLATFORM_LINUX
#   include <SDL2/SDL.h>
#endif

Area Area::areaControl;


Area::Area() {
    areaSize = 0;
}

bool Area::loadArea(const char* file) {
    listMap.clear();

    //Open file and check error
    FILE* filehandler = fopen(file, "r");
    if(filehandler == NULL) {
        LOG_ERROR("Unable to open file");
        return false;
    }

    //Recover the tilesSpriteFile (sprite-sheet)
    char tilesSpriteFile[255];
    fscanf(filehandler, "%s\n", tilesSpriteFile);
    tilesSprites = Surface::loadFromFile(tilesSpriteFile);

    if(tilesSprites==NULL) {
        LOG_ERROR("Unable to load the sprite sheet");
        fclose(filehandler);
        return false; 
    }

    //Recover area size
    fscanf(filehandler, "%d\n", &areaSize);

    //Recover each map
    for(int x = 0; x<areaSize; x++) {
        for(int y = 0; y<areaSize; y++) {
            char mapFile[255];
            fscanf(filehandler, "%s ", mapFile);
            Map tmpMap;

            if(tmpMap.loadMapFromFile(mapFile)==false) {
                LOG_ERROR("Unable to load the map");
                fclose(filehandler);
                return false;
            }

            tmpMap.m_tilesSprites = tilesSprites;
            listMap.push_back(tmpMap);
        }
        fscanf(filehandler, "\n");
    }
    fclose(filehandler);
    return true;
}

void Area::renderArea(SDL_Surface * dest, int cameraX, int cameraY) {
    if(dest==NULL) { return; }

    //Actual map size in window (In pixels) (Update: Can be calculated before)
    int mapW = MAP_NB_TILES_WIDTH * TILE_SIZE;
    int mapH = MAP_NB_TILES_HEIGHT * TILE_SIZE;

    //Get the ID of the first map to display (Don't draw map outside the camera)
    int firstID = -cameraX/mapW;
    firstID = firstID+((-cameraY/mapH) * areaSize);

    //Render the maps to display
    //For the defined screen size (640*480), only 4 map need to be displayed
    for(int i = 0; i<4; i++) {
        int id = firstID+((i/2) * areaSize)+(i%2);

        if(id<0||id>=listMap.size()) {
            continue;
        }

        int x = ((id%areaSize) * mapW)+cameraX;
        int y = ((id/areaSize) * mapH)+cameraY;
        listMap[id].renderMap(dest, x, y);
    }
}

void Area::cleanupArea() {
    SDL_FreeSurface(tilesSprites);
    listMap.clear();
}

Map* Area::getMap(int posX, int posY) {
    int mapPixelWidth = TILE_SIZE * MAP_NB_TILES_WIDTH;
    int mapPixelHeigh = TILE_SIZE * MAP_NB_TILES_HEIGHT;
    int id = (posX/mapPixelWidth) + (areaSize*(posY/mapPixelHeigh));

    if(id<0 || id>= listMap.size()) {
        return nullptr;
    }

    return &listMap[id];
}

Tile* Area::getTile(int posX, int posY) {
    int mapPixelWidth = TILE_SIZE * MAP_NB_TILES_WIDTH;
    int mapPixelHeigh = TILE_SIZE * MAP_NB_TILES_HEIGHT;
    Map* map = getMap(posX, posY);

    if(map==nullptr) {
        return nullptr;
    }

    posX = posX % mapPixelWidth;
    posY = posY % mapPixelHeigh;
    return map->getTile(posX, posY);
}
