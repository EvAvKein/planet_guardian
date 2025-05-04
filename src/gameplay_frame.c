#include "planet_guardian.h"

void gameplay_frame()
{
	// --- Calculate Shield Collision Circles ---
	float orbitRadius = game.planet.radius + 50.0f;
	Vector2 planetCenter = game.planet.center_pos;
	Vector2 shieldMidPoint = {
		planetCenter.x + cosf(game.shield.angle) * orbitRadius,
		planetCenter.y + sinf(game.shield.angle) * orbitRadius
	};
	Vector2 tangentDir = {-sinf(game.shield.angle), cosf(game.shield.angle)};

	// --- Shield Circle Parameters (TUNABLE) ---
	float shieldSegmentOffset = game.shield.sprite.texture.width * 0.4f;
	float shieldSegmentRadius = game.shield.sprite.texture.width * 0.15;
	Vector2 shieldCircle1Center = Vector2Add(shieldMidPoint, Vector2Scale(tangentDir, shieldSegmentOffset));
	Vector2 shieldCircle2Center = Vector2Add(shieldMidPoint, Vector2Scale(tangentDir, -shieldSegmentOffset));
	shieldSegmentRadius = game.shield.sprite.texture.width * 0.093f;
	Vector2 shieldCircle3Center = Vector2Add(shieldMidPoint, Vector2Scale(tangentDir, -shieldSegmentOffset * 0.2));
	Vector2 shieldCircle4Center = Vector2Add(shieldMidPoint, Vector2Scale(tangentDir, shieldSegmentOffset * 0.2));
	shieldSegmentRadius = game.shield.sprite.texture.width * 0.12f;
	Vector2 shieldCircle5Center = Vector2Add(shieldMidPoint, Vector2Scale(tangentDir, -shieldSegmentOffset * 0.7));
	Vector2 shieldCircle6Center = Vector2Add(shieldMidPoint, Vector2Scale(tangentDir, shieldSegmentOffset * 0.7));


	if (IsKeyPressed(KEY_SPACE))
			game.shield.direction = -game.shield.direction;
	float deltaTime = GetFrameTime();
	game.shield.angle += deltaTime * game.shield.spin_speed * game.shield.direction; // Get time elapsed since last frame
	// if (IsKeyDown(KEY_LEFT))
	// 	shieldAngle -= deltaTime * 3.0f;  // Get time elapsed since last frame

	// Initialize asteroids
	// float spawnDelay = 3.0f;  // Delay in seconds before spawning new asteroid
	// float totalTime = 0.0f;  // Total elapsed time
	// int asteroid1;
	// int asteroid2;
	int i = 0;
	while (i < MAX_ASTEROIDS)
	{
		game.asteroid[i].center_pos.x = game.asteroid[i].pos.x + game.asteroid[i].radius;
		game.asteroid[i].center_pos.y = game.asteroid[i].pos.y + game.asteroid[i].radius;
		if (CheckCollisionCircles(game.planet.center_pos, game.planet.radius, game.asteroid[i].center_pos, game.asteroid[i].radius))
		{
			if (!--game.current_health)
			{
				game.state = END;
				game.lose_reason = METEORS;
				game.time_since_death = 0;
				return ;
			};
			game.asteroid[i] = initialize_asteroid(game.asteroid[i]);
		}
		game.asteroid[i].pos = moveTowardsWithGravity(game.asteroid[i].pos, game.asteroid[i].direction, game.asteroid[i].speed, game.planet.center_pos);

		if (CheckCollisionCircles(game.asteroid[i].center_pos, game.asteroid[i].radius, shieldCircle1Center, shieldSegmentRadius) ||
		CheckCollisionCircles(game.asteroid[i].center_pos, game.asteroid[i].radius, shieldCircle2Center, shieldSegmentRadius) ||
		CheckCollisionCircles(game.asteroid[i].center_pos, game.asteroid[i].radius, shieldCircle3Center, shieldSegmentRadius)||
		CheckCollisionCircles(game.asteroid[i].center_pos, game.asteroid[i].radius, shieldCircle4Center, shieldSegmentRadius)||
		CheckCollisionCircles(game.asteroid[i].center_pos, game.asteroid[i].radius, shieldCircle5Center, shieldSegmentRadius)||
		CheckCollisionCircles(game.asteroid[i].center_pos, game.asteroid[i].radius, shieldCircle6Center, shieldSegmentRadius))
		{
				play_shield_sound();
				game.asteroid[i] = initialize_asteroid(game.asteroid[i]);
		}
		i++;
	}
	initialize_out_of_bounds_asteroids();
	check_colliding_asteroids();
		// float deltaTime = GetFrameTime();  // Get time elapsed since last frame
		// totalTime += deltaTime;

	BeginDrawing();
		ClearBackground(BLACK);

		// DrawTexturePro(game.background, (Rectangle){.x = 0, .y = 0,
		// 		.width = game.background.width, .height = game.background.height},
		// 	(Rectangle){.x = game.background.width, .y = game.background.height,
		// 		.width = SCREEN_WIDTH, .height = SCREEN_HEIGHT},
		// 	(Vector2){.x = game.background.width, .y = game.background.height},
		// 	0,
		// 	WHITE);
	draw_repeat_background(SCREEN_WIDTH, SCREEN_HEIGHT);

		update_planet_condition(deltaTime, game.shield.angle);
		if (game.temp.value == MAX_TEMP)
		{
			game.state = END;
			game.lose_reason = HEAT;
			game.time_since_death = 0;
			return ;
		}
		if (game.temp.value == MIN_TEMP)
		{
			game.state = END;
			game.lose_reason = COLD;
			game.time_since_death = 0;
			return ;
		}
		
            float healthBarWidthMax = 150.0f;
            float healthBarHeight = 25.0f;
            Vector2 healthBarPos = { 10.0f, 10.0f };

            float healthRatio = 0.0f;
            if (MAX_HEALTH > 0) {
                 healthRatio = (float)game.current_health / (float)MAX_HEALTH;
            }
            float currentHealthBarWidth = healthBarWidthMax * healthRatio;
            if (currentHealthBarWidth < 0) currentHealthBarWidth = 0;

            DrawRectangleV(healthBarPos, (Vector2){healthBarWidthMax, healthBarHeight}, DARKGRAY);
            if ((float)(game.current_health / (float)MAX_HEALTH) > 0.7)
				DrawRectangleV(healthBarPos, (Vector2){currentHealthBarWidth, healthBarHeight}, GREEN);
			else if ((float)(game.current_health / (float)MAX_HEALTH) > 0.3)
				DrawRectangleV(healthBarPos, (Vector2){currentHealthBarWidth, healthBarHeight}, YELLOW);
			else if ((float)(game.current_health / (float)MAX_HEALTH) > -1.0)
				DrawRectangleV(healthBarPos, (Vector2){currentHealthBarWidth, healthBarHeight}, RED);
            DrawRectangleLinesEx((Rectangle){healthBarPos.x, healthBarPos.y, healthBarWidthMax, healthBarHeight}, 2.0f, BLACK);

		DrawTextureV(game.planet.texture, game.planet.pos, WHITE);
		if (game.temp.value > 0) 
			DrawTextureV(game.temp.hot_texture, game.planet.pos,
				(Color){.r = 255, .g = 255, .b = 255, .a = game.temp.value});
		else if (game.temp.value < 0) 
			DrawTextureV(game.temp.cold_texture, game.planet.pos,
				(Color){.r = 255, .g = 255, .b = 255, .a = -game.temp.value});

		DrawTexturePro(game.shadow.texture,
			(Rectangle){.x = 0, .y = 0,
				.height = game.shadow.texture.height, .width = game.shadow.texture.width},
			(Rectangle){.x = SCREEN_WIDTH / 2, .y = SCREEN_HEIGHT / 2,
				.height = game.shadow.texture.height, .width = game.shadow.texture.width},
			(Vector2){.x = game.planet.texture.width / 2, .y = game.planet.texture.height / 2},
			game.shadow.rotation,
			(Color){.r = 0, .g = 0, .b = 0, .a = 150});
		draw_shield(game.shield.angle);
		draw_asteroids();
	EndDrawing();
}
