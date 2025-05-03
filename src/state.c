#include "planet_guardian.h"

void drawMenu() {
    DrawTextureRec(game.menu, (Rectangle){40, 200, 120, 200}, (Vector2){0, 0}, WHITE); 
    printp("PRESS SPACE", 600, 300, 1.0f, RED);
    while(!IsKeyPressed(KEY_SPACE))
        ;
}

void deathScreen() {

}