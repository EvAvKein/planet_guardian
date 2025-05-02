#include "planet_guardian.h"
#include "raylib.h"

#define MAX_BUILDINGS	100

int main(void)
{
	const int	SCREEN_WIDTH = 1920;
	const int	SCREEN_HEIGHT = 1080;
	int			frames_counter;
	int			spacing;
	game_screen	current_screen;

	Rectangle	player= { 400, 280, 40, 40 };
	Rectangle	buildings[MAX_BUILDINGS] = { 0 };
	Color		building_colors[MAX_BUILDINGS] = { 0 };

	spacing = 0;
	for (int i = 0; i < MAX_BUILDINGS; i++)
	{
		buildings[i].width = (float)GetRandomValue(50, 200);
		buildings[i].height = (float)GetRandomValue(100, 800);
		buildings[i].y = SCREEN_HEIGHT - 130.0f - buildings[i].height;
		buildings[i].x = -6000.0f + spacing;

		spacing += (int)buildings[i].width;

		building_colors[i] = (Color)
		{
			(unsigned char)GetRandomValue(200, 240),
			(unsigned char)GetRandomValue(200, 240),
			(unsigned char)GetRandomValue(200, 250),
			255
		};
	}

	// Camera 2d NEXT
	frames_counter = 0;
	current_screen = LOGO;
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Jam!");
	SetTargetFPS(60);
	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		switch (current_screen)
		{
			case LOGO:
			{
				frames_counter++;
				if (frames_counter > 120)
					current_screen = TITLE;
			}
			break ;
			case TITLE:
			{
				if (IsKeyPressed(KEY_ENTER))
					current_screen = GAMEPLAY;
			}
			break ;
			case GAMEPLAY:
			{
				if (IsKeyPressed(KEY_ENTER))
					current_screen = ENDING;
			}
			break ;
			case ENDING:
			{
				if (IsKeyPressed(KEY_ENTER))
					current_screen = TITLE;
			}
			break ;
		}
		BeginDrawing();
		ClearBackground(RAYWHITE);
		switch (current_screen)
		{
			ClearBackground(RAYWHITE);
			case LOGO:
			{
				DrawText("LOGOSCREEN", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 20, LIGHTGRAY);
			}
			break ;
			case TITLE:
			{
				DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, DARKGREEN);
				DrawText("Press ENTER to continue...", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 20, LIGHTGRAY);
			}
			break ;
			case GAMEPLAY:
			{
				DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, PURPLE);
				DrawText("Gameplay screen\nPress ENTER to continue...", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 20, LIGHTGRAY);
			}
			break ;
			case ENDING:
			{
				DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLUE);
				DrawText("Ending screen\nPress ENTER to continue...", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 20, LIGHTGRAY);
			}
			break ;
		}
		EndDrawing();
	}

	CloseWindow();

	return (EXIT_SUCCESS);
}
