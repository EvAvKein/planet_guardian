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
        const char *gameOverText = ft_strjoin("LOST TO ", 
            game.lose_reason == HEAT ? "HEAT"
            : game.lose_reason == COLD ? "COLDNESS"
            : "METEORS");
        if (!gameOverText)
        {
            dprintf(2, "Malloc failed in ft_strjoin :( \n");
            return ;
        }
        Vector2 textSize = MeasureTextEx(game.font, gameOverText, game.font.baseSize * 2.0f, 2.0f);
    DrawTextEx(game.font, gameOverText,
        (Vector2){(GetScreenWidth() - textSize.x) / 2.0f, (GetScreenHeight() - textSize.y) / 2.0f - 30},
        game.font.baseSize * 2.0f, 2.0f, RED);

    // Texture2D lose_asset = game.lose_textures[game.lose_reason];
    // DrawTexture(lose_asset,
    //     GetScreenWidth() / 2 - (lose_asset.width / 2),
    //     GetScreenHeight() / 4 - (lose_asset.height / 2) - 10,
    //     WHITE);

    const char* restartText = "Press [SPACE] to Restart";
    Vector2 restartTextSize = MeasureTextEx(game.font, restartText, game.font.baseSize, 1.5f);
    DrawTextEx(game.font, restartText,
        (Vector2){(GetScreenWidth() - restartTextSize.x) / 2.0f, (GetScreenHeight() - restartTextSize.y) / 2.0f + 100},
        game.font.baseSize, 1.0f, GRAY);
    char scoreText[100];
	snprintf(scoreText, sizeof(scoreText), "You survived for %.2f seconds", game.time_since_live);

	Vector2 scoreTextSize = MeasureTextEx(game.font, scoreText, game.font.baseSize, 1.0f);
	DrawTextEx(game.font, scoreText,
    	(Vector2){(GetScreenWidth() - scoreTextSize.x) / 2.0f, (GetScreenHeight() - scoreTextSize.y) / 2.0f + 40},
	    game.font.baseSize, 1.0f, WHITE);
    
    game.time_since_death += GetFrameTime();
    if (game.time_since_death > 1.0f && IsKeyPressed(KEY_SPACE)) {
        PlaySound(game.sound.theme);
        initialize_all_asteroids();
        game.current_health = MAX_HEALTH;
        game.shield.angle = 0.0f;
        game.state = GAME;
        game.temp.value = 0;
	game.time_since_live = 0;
    }
    EndDrawing();
}
