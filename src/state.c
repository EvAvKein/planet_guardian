#include "planet_guardian.h"

void drawMenu() {
    ClearBackground(RED);
    printp("PRESS SPACE", 600, 300, 1.0f, RED);
    if(IsKeyPressed(KEY_SPACE))
        game.state = GAME;
    
}

void deathScreen() {
    printp("YOU LOST", 400, 400, 1.0f, DARKPURPLE);
    if(IsKeyPressed(KEY_SPACE))
        game.state = GAME;
}