#ifndef SCREEN_H
#define SCREEN_H

#include <stdio.h>
#include <stdbool.h>

#include "SDL.h"
#include "Config.h"

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} Screen;

bool Screen_Init(Screen* screen);
void Screen_Destroy(Screen* screen);

#endif