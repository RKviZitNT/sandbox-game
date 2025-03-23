#include "Game.h"

int main (int argc, char ** args) {
    Game_Init();
    Game_RunLoop();
    Game_Destroy();

    return 0;
};