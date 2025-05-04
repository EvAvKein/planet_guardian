#include "planet_guardian.h"

void drawMenu() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexturePro(game.menu, (Rectangle){0, 0, 256, 256}, (Rectangle){0, 0, GetScreenHeight(), GetScreenWidth()},(Vector2){0, 0}, 0, WHITE);
    printp("PRESS SPACE", 300, 600, 1.0f, RED);
    if(IsKeyPressed(KEY_SPACE))
        game.state = GAME;
    EndDrawing();
}

void deathScreen() {
    BeginDrawing();
    printp("YOU LOST.\n RETRY?", 400, 400, 1.0f, DARKPURPLE);
    if(IsKeyPressed(KEY_SPACE))
    {
        game.state = GAME;
        game.temp.value = 0;
    }
    EndDrawing();
}
