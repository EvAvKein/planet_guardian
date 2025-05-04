#include "planet_guardian.h"

void drawMenu() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexturePro(game.menu, (Rectangle){0, 0, 256, 256}, (Rectangle){0, 0, GetScreenHeight(), GetScreenWidth()},(Vector2){0, 0}, 0, WHITE);
    printp("PRESS SPACE", GetScreenWidth() * 0.5, GetScreenHeight() * 0.5, 1.0f, RED);
    if(IsKeyPressed(KEY_SPACE)) {
        game.state = GAME;
        playTheme();
    }
    EndDrawing();
}

void deathScreen() {
    BeginDrawing();
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.7f));
        const char* gameOverText = "GAME OVER";
        Vector2 textSize = MeasureTextEx(game.font, gameOverText, game.font.baseSize * 2.0f, 2.0f);
    DrawTextEx(game.font, gameOverText,
        (Vector2){(GetScreenWidth() - textSize.x) / 2.0f, (GetScreenHeight() - textSize.y) / 2.0f - 30},
        game.font.baseSize * 2.0f, 2.0f, RED);

    const char* restartText = "Press [SPACE] to Restart";
    Vector2 restartTextSize = MeasureTextEx(game.font, restartText, game.font.baseSize, 1.0f);
    DrawTextEx(game.font, restartText,
        (Vector2){(GetScreenWidth() - restartTextSize.x) / 2.0f, (GetScreenHeight() - restartTextSize.y) / 2.0f + 40},
        game.font.baseSize, 1.0f, WHITE);

    game.time_since_death += GetFrameTime();
    if (game.time_since_death > 1.0f && IsKeyPressed(KEY_SPACE)) {
        PlaySound(game.sound.theme);
        initialize_all_asteroids();
        game.current_health = MAX_HEALTH;
        game.shield.angle = 0.0f;
        game.state = GAME;
        game.temp.value = 0;
    }
    EndDrawing();
}
