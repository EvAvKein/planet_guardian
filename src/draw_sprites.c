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
		Vector2 position = game.asteroid[i].center_pos;
		Texture2D tex = game.asteroid[i].texture;
		float rotation = game.asteroid[i].rotation;
		DrawTexturePro(
			tex,
			(Rectangle){ 0, 0, tex.width, tex.height },
			(Rectangle){ position.x, position.y, tex.width, tex.height },
			(Vector2){ tex.width / 2.0f, tex.height / 2.0f }, // Origopiste keskelle
			rotation,
			WHITE);
		if (i % 2 == 0)
			game.asteroid[i].rotation += 90.0f * GetFrameTime(); // Myötäpäivään
		else
			game.asteroid[i].rotation -= 90.0f * GetFrameTime(); // Vastapäivään
		i++;
	}
}

void draw_repeat_background(int	screen_width, int screen_height)
{
	Vector2 bg_pos = { 0, 0 };

	while (bg_pos.y < screen_height)
	{
		bg_pos.x = 0;
		while (bg_pos.x < screen_width)
		{
			DrawTextureV(game.background, bg_pos, WHITE);
			bg_pos.x += game.background.width;
		}
		bg_pos.y += game.background.height;
	}
}
