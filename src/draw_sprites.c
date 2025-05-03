#include "planet_guardian.h"

void draw_asteroids()
{
	// float totalTime = 0.0f;  // Total elapsed time
	// float deltaTime = GetFrameTime();  // Get time elapsed since last frame
	// float spawnDelay = 3.0f;  // Delay in seconds before spawning new asteroid
	// totalTime += deltaTime;
	//
//	if (totalTime > spawnDelay)
	int i = 0;
	while (i < MAX_ASTEROIDS)
	{
		DrawTextureV(game.asteroid[i].texture, game.asteroid[i].pos, WHITE);
		i++;
	}
}
