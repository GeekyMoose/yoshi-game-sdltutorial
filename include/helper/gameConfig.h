#pragma once


#include <SDL2/SDL.h>


enum {
    WINDOW_DEFAULT_WIDTH        = 640,
    WINDOW_DEFAULT_HEIGHT       = 640,
    WINDOW_DEFAULT_POS_LEFT     = SDL_WINDOWPOS_UNDEFINED,
    WINDOW_DEFAULT_POS_RIGHT    = SDL_WINDOWPOS_UNDEFINED
};

enum {
    MAP_NB_TILES_WIDTH          = 40,
    MAP_NB_TILES_HEIGHT         = 40,
    TILE_SIZE                   = 16
};

enum {
    FPS_FIXED_TIME              = 60
};

#define GAME_CONFIG_WINDOW_TITLE "2d game"
#define GAME_CONFIG_WINDOW_DEFAULT_MODE SDL_WINDOW_HIDDEN
