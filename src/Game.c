#include "Game.h"

Screen screen = {NULL, NULL};

SDL_Event event;
Pixel pixel;

int currentPixelType = PIXEL_SAND;

bool running = true;

static void HandleEvents() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }

        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_1:
                    currentPixelType = PIXEL_SAND;
                    break;
                case SDLK_2:
                    currentPixelType = PIXEL_STONE;
                    break;
                case SDLK_3:
                    currentPixelType = PIXEL_WATER;
                    break;
            }
        }        
    }

    printf("%d\n", currentPixelType);

    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    if (mouseState & SDL_BUTTON_LMASK) {
        SandBox_CreatePixel(currentPixelType, mouseX, mouseY);
    }
    else if (mouseState & SDL_BUTTON_RMASK) {
        SandBox_CreatePixel(PIXEL_EMPTY, mouseX, mouseY);
    }
}


static void Update() {
    SandBox_Update();
}

static void Draw() {
    SDL_SetRenderDrawColor(screen.renderer, 0, 0, 0, 255);
    SDL_RenderClear(screen.renderer);

    int x = 0, y = 0;

    while (SandBox_DrawingPixels(&pixel)) {
        SDL_SetRenderDrawColor(screen.renderer, pixel.r, pixel.g, pixel.b, 255);
        SDL_Rect rect = { x, y, PIXEL, PIXEL };
        SDL_RenderFillRect(screen.renderer, &rect);

        if (x >= SCREEN_WIDTH * PIXEL) {
            x = 0;
            y += PIXEL;
        }
        else {
            x += PIXEL;
        }
    }
    
    SDL_RenderPresent(screen.renderer);
}

void Game_Init() {
    if (!Screen_Init(&screen)) {
        running = false;
        return;
    }
    
    SandBox_Init();
}

void Game_RunLoop() {
    const int targetFrameTime = 1000 / FRAME_RATE;
    Uint32 startTime, frameTime;

    while (running) {
        startTime = SDL_GetTicks();

        HandleEvents();
        Update();
        Draw();

        frameTime = SDL_GetTicks() - startTime;
        if (frameTime < targetFrameTime) {
            SDL_Delay(targetFrameTime - frameTime);
        }
    } 
}

void Game_Destroy() {
    Screen_Destroy(&screen);
}