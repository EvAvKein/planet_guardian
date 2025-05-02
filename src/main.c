#include "planet_guardian.h"

game_t game;

void textureLoader()
{
	Image image = LoadImage("assets/graphics/icon.png");
	Texture2D texture = LoadTextureFromImage(image);
	game.planet = texture;
	UnloadImage(image);
	image = LoadImage("assets/graphics/icon.png");
	Texture2D texture1 = LoadTextureFromImage(image);
	game.asteroid = texture1;
	UnloadImage(image);
}

void textureUnload()
{
	UnloadTexture(game.planet);
	UnloadTexture(game.asteroid);
}

int main(void)
{
	const int screenWidth = 800;
    const int screenHeight = 800;
	InitWindow(500, 500, "Jam!");

	textureLoader();

	int x = (screenWidth - game.planet.width) / 2;
	int y = (screenHeight - game.planet.height) / 2;


	while (!WindowShouldClose())
	{
		BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawTexture(game.planet, y, x, WHITE);
		EndDrawing();
	}

	textureUnload();
	CloseWindow();

	return (EXIT_SUCCESS);
}
