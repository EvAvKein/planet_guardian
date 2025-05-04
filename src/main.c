#include "planet_guardian.h"

game_t game;

void initialize_game()
{
  	game.current_health = MAX_HEALTH;
	
	game.shield.angle = 0.0f;
	game.shield.direction = 1;

	game.temp.interval = 0.15f;
	game.shadow.interval = 0.15f;

	game.planet.pos.x = (SCREEN_WIDTH - game.planet.texture.width) / 2.0f;
	game.planet.pos.y = (SCREEN_HEIGHT - game.planet.texture.height) / 2.0f;
	game.planet.center_pos.x = game.planet.pos.x + game.planet.texture.width / 2.0f;
	game.planet.center_pos.y = game.planet.pos.y + game.planet.texture.width / 2.0f;
	// Aim to the middle of the planet
	// calculating the target to the middle
}

int main(void)
{
	srand(time(NULL));

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Planet Guardian");
	SetTargetFPS(60);
	textureLoader();

	initialize_game();
	initialize_all_asteroids();
	InitAudioDevice();
	soundLoader();
	while (!WindowShouldClose())
	{
			switch(game.state) {
				case START:
					drawMenu();
					break;
				case GAME:
					gameplay_frame();
					break;
				case END:
					deathScreen();
			}
	}
	textureUnload();

	CloseWindow();
	return (EXIT_SUCCESS);
}
