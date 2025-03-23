#include "Screen.h"

bool Screen_Init(Screen* screen) {
    SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init error: %s\n", SDL_GetError());
        return false;
    }

    screen->window = SDL_CreateWindow("SandBox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH * PIXEL, SCREEN_HEIGHT * PIXEL, SDL_WINDOW_SHOWN);
    if (!screen->window) {
        printf("SDL_CreateWindow error: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    screen->renderer = SDL_CreateRenderer(screen->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!screen->renderer) {
        printf("SDL_CreateRenderer error: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    return true;
}

void Screen_Destroy(Screen* screen) {
    SDL_DestroyRenderer(screen->renderer);
    SDL_DestroyWindow(screen->window);
    SDL_Quit();
}