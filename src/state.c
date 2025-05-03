#include "planet_guardian.h"

void drawMenu() {
<<<<<<< HEAD
    ClearBackground(BLACK);
    DrawTexturePro(game.menu, (Rectangle){0, 0, 256, 256}, (Rectangle){0, 0, GetScreenHeight(), GetScreenWidth()},(Vector2){0, 0}, 0, WHITE);
    printp("PRESS SPACE", 300, 600, 1.0f, RED);
=======
    DrawTextureRec(game.menu, (Rectangle){40, 200, 120, 200}, (Vector2){0, 0}, WHITE); 
    printp("PRESS SPACE", 600, 300, 1.0f, RED);
>>>>>>> 9643e61d0bbb6ab50c07a04a567e578f4a12400b
    if(IsKeyPressed(KEY_SPACE))
        game.state = GAME;
}

void deathScreen() {
<<<<<<< HEAD
    printp("YOU LOST.\n RETRY?", 400, 400, 1.0f, DARKPURPLE);
    if(IsKeyPressed(KEY_SPACE))
        game.state = GAME;
=======

>>>>>>> 9643e61d0bbb6ab50c07a04a567e578f4a12400b
}