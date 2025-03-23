#ifndef SANDBOX_H
#define SANDBOX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "Config.h"

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Pixel;

enum PixelType {
    PIXEL_EMPTY,
    PIXEL_SAND,
    PIXEL_STONE,
    PIXEL_WATER
};

void SandBox_Init();
void SandBox_Update();
bool SandBox_DrawingPixels(Pixel *pixel);
void SandBox_CreatePixel(int pixelType, int xpos, int ypos);

#endif