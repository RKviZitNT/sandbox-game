#include "SandBox.h"

static int pixelBuffer[SCREEN_HEIGHT][SCREEN_WIDTH];
static int pixelBufferUpdate[SCREEN_HEIGHT][SCREEN_WIDTH];

Pixel empty;
Pixel sand;
Pixel stone;
Pixel water;

static int currentPixelType = PIXEL_SAND;

void SandBox_Init() {
    for (size_t y = 0; y < SCREEN_HEIGHT; y++) {
        for (size_t x = 0; x < SCREEN_WIDTH; x++) {
            pixelBuffer[y][x] = PIXEL_EMPTY;
            pixelBufferUpdate[y][x] = PIXEL_EMPTY;
        }
    }

    // pixelBuffer[SCREEN_HEIGHT-1]

    empty = (Pixel){ 0, 0, 0 };
    sand = (Pixel){ 255, 255, 0 };
    stone = (Pixel){ 127, 127, 127 };
    water = (Pixel){ 0, 0, 255 };
}

void SandBox_Update() {
    for (int y = SCREEN_HEIGHT-1; y >= 0; y--) {
        for (int x = SCREEN_WIDTH-1; x >= 0; x--) {
            switch (pixelBuffer[y][x]) {
                case PIXEL_SAND:
                    if (y < SCREEN_HEIGHT-1) {
                        if (pixelBufferUpdate[y+1][x] == PIXEL_EMPTY) {
                            pixelBufferUpdate[y+1][x] = PIXEL_SAND;
                            break;
                        }
                        else if (x > 0 && pixelBuffer[y][x-1] == PIXEL_EMPTY && pixelBufferUpdate[y+1][x-1] == PIXEL_EMPTY) {
                            pixelBufferUpdate[y+1][x-1] = PIXEL_SAND;
                            break;
                        }
                        else if (x < SCREEN_WIDTH-1 && pixelBufferUpdate[y][x+1] == PIXEL_EMPTY && pixelBufferUpdate[y+1][x+1] == PIXEL_EMPTY) {
                            pixelBufferUpdate[y+1][x+1] = PIXEL_SAND;
                            break;
                        }
                        else {
                            pixelBufferUpdate[y][x] = PIXEL_SAND;
                            break;
                        }
                    }
                    else {
                        pixelBufferUpdate[y][x] = PIXEL_SAND;
                        break;
                    }

                case PIXEL_WATER:
                    if (y < SCREEN_HEIGHT-1) {
                        if (pixelBufferUpdate[y+1][x] == PIXEL_EMPTY) {
                            pixelBufferUpdate[y+1][x] = PIXEL_WATER;
                            break;
                        }
                        else if (pixelBuffer[y-1][x] == PIXEL_SAND) {
                            pixelBuffer[y-1][x] = PIXEL_WATER;
                            pixelBufferUpdate[y][x] = PIXEL_SAND;
                            break;
                        }
                        else if (x > 0 && pixelBuffer[y][x-1] == PIXEL_EMPTY && pixelBufferUpdate[y+1][x-1] == PIXEL_EMPTY) {
                            pixelBufferUpdate[y+1][x-1] = PIXEL_WATER;
                            break;
                        }
                        else if (x < SCREEN_WIDTH-1 && pixelBufferUpdate[y][x+1] == PIXEL_EMPTY && pixelBufferUpdate[y+1][x+1] == PIXEL_EMPTY) {
                            pixelBufferUpdate[y+1][x+1] = PIXEL_WATER;
                            break;
                        }
                        else if (x > 0 && pixelBuffer[y][x-1] == PIXEL_EMPTY) {
                            pixelBufferUpdate[y][x-1] = PIXEL_WATER;
                            break;
                        }
                        else if (x < SCREEN_WIDTH-1 && pixelBufferUpdate[y][x+1] == PIXEL_EMPTY) {
                            pixelBufferUpdate[y][x+1] = PIXEL_WATER;
                            break;
                        }
                        else {
                            pixelBufferUpdate[y][x] = PIXEL_WATER;
                            break;
                        }
                    }
                    else {
                        pixelBufferUpdate[y][x] = PIXEL_WATER;
                        break;
                    }
                
                case PIXEL_STONE:
                    pixelBufferUpdate[y][x] = PIXEL_STONE;
                    break;

                default:
                    break;
            }
        }
    }

    for (size_t y = 0; y < SCREEN_HEIGHT; y++) {
        for (size_t x = 0; x < SCREEN_WIDTH; x++) {
            pixelBuffer[y][x] = pixelBufferUpdate[y][x];
            pixelBufferUpdate[y][x] = PIXEL_EMPTY;
        }
    }
}

bool SandBox_DrawingPixels(Pixel *pixel) {
    static size_t x = 0, y = 0;

    while (x * y < SCREEN_WIDTH * SCREEN_HEIGHT) {
        switch (pixelBuffer[y][x]){
            case PIXEL_EMPTY:
                *pixel = empty;
                break;
            case PIXEL_SAND:
                *pixel = sand;
                break;
            case PIXEL_STONE:
                *pixel = stone;
                break;
            case PIXEL_WATER:
                *pixel = water;
                break;
            default:
                break;
        }

        if (x >= SCREEN_WIDTH) {
            x = 0;
            y++;
        }
        else {
            x++;
        }
        
        return true;
    }

    x = y = 0;
    return false;
}

void SandBox_CreatePixel(int pixelType, int xpos, int ypos) {
    int x = xpos / PIXEL;
    int y = ypos / PIXEL;

    if (pixelType == PIXEL_EMPTY) {
        pixelBuffer[y][x] = pixelType;
    }
    else if (pixelBuffer[y][x] == PIXEL_EMPTY) {
        pixelBufferUpdate[y][x] = pixelType;
    }
}