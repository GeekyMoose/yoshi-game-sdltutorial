#include "sdl/AppWindowSDL2.h"

#include "utils/gameConfig.h"
#include "utils/log.h"

#include <iostream>


//------------------------------------------------------------------------------
// Initialization
//------------------------------------------------------------------------------
AppWindowSDL2::~AppWindowSDL2() {
    this->destroy();
}

void AppWindowSDL2::initialize() {
    this->m_SDLwindow = SDL_CreateWindow(
        GAME_CONFIG_WINDOW_TITLE,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_DEFAULT_WIDTH,
        WINDOW_DEFAULT_HEIGHT,
        SDL_WINDOW_HIDDEN
    );

    if(this->m_SDLwindow == NULL) {
        LOG_ERROR("SDL error: %s", SDL_GetError());
        return;
    }

    //Load SDL_Surface from the window
    this->m_SDLsurface = SDL_GetWindowSurface(this->m_SDLwindow);
    SDL_FillRect(this->m_SDLsurface, NULL, SDL_MapRGB(this->m_SDLsurface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(this->m_SDLwindow);
}

void AppWindowSDL2::destroy() {
    SDL_FreeSurface(this->m_SDLsurface);
    SDL_DestroyWindow(this->m_SDLwindow);
}


//------------------------------------------------------------------------------
// Other methods
//------------------------------------------------------------------------------

void AppWindowSDL2::show() {
    SDL_ShowWindow(this->m_SDLwindow);
}

void AppWindowSDL2::hide() {
    SDL_HideWindow(this->m_SDLwindow);
}

void AppWindowSDL2::maximize() {
    SDL_MaximizeWindow(this->m_SDLwindow);
}

void AppWindowSDL2::minimize() {
    SDL_MinimizeWindow(this->m_SDLwindow);
}

void AppWindowSDL2::update() {
    SDL_UpdateWindowSurface(this->m_SDLwindow);
}

void AppWindowSDL2::clear() {
    SDL_FillRect(this->m_SDLsurface, NULL,
            SDL_MapRGB(
                this->m_SDLsurface->format, 0x00, 0x00, 0x00));
}
