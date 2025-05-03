#include "planet_guardian.h"

game_t game;



void textureLoader()
{
	Image image = LoadImage("assets/graphics/earth_normal.png");
	game.font = LoadFontEx("assets/fonts/PIXY.ttf", 32, 0, 250);
	Texture2D texture = LoadTextureFromImage(image);
	game.planet.texture = texture;
	game.planet.radius = texture.height / 2.0f;
	UnloadImage(image);
	Texture2D texture_zero = LoadTexture("assets/graphics/earth_snow.png");
	game.cold.texture = texture_zero;
	image = LoadImage("assets/graphics/earth_normal.png");
	ImageCrop(&image, (Rectangle){
		.height = image.height, .width = image.width / 2});
	Texture2D texture_shadow = LoadTextureFromImage(image);
	game.shadow.texture = texture_shadow;
	game.background = LoadTexture("assets/graphics/background_1-64x64.png");
	UnloadImage(image);
	// image = LoadImage("assets/graphics/asteroid.png");
	// Texture2D texture1 = LoadTextureFromImage(image);
	// game.asteroid[0].texture = texture1;
	// UnloadImage(image);
	// image = LoadImage("assets/graphics/asteroid2.png");
	// Texture2D texture2 = LoadTextureFromImage(image);
	// game.asteroid[1].texture = texture2;
	// game.asteroid[1].radius = texture2.height / 2.0f;
	// UnloadImage(image);
	// image = LoadImage("assets/graphics/asteroid.png");
	// Texture2D texture3 = LoadTextureFromImage(image);
	// game.asteroid[2].texture = texture3;
	// game.asteroid[2].radius = texture3.height / 2.0f;
	// UnloadImage(image);
	// image = LoadImage("assets/graphics/asteroid2.png");
	// Texture2D texture4 = LoadTextureFromImage(image);
	// game.asteroid[3].texture = texture4;
	// game.asteroid[3].radius = texture3.height / 2.0f;
	// UnloadImage(image);
	// image = LoadImage("assets/graphics/asteroid.png");
	// Texture2D texture5 = LoadTextureFromImage(image);
	// game.asteroid[4].texture = texture5;
	// game.asteroid[4].radius = texture4.height / 2.0f;
	// UnloadImage(image);
	image = LoadImage("assets/graphics/shield.png");
	Texture2D texture6 = LoadTextureFromImage(image);
	game.shield.texture = texture6;
	game.shield.radius = texture6.height / 2.0f;

// TEST
	int i = 0;
	image = LoadImage("assets/graphics/asteroid2.png");
	Texture2D asteroid_texture = LoadTextureFromImage(image);
	while (i < MAX_ASTEROIDS)
	{
		game.asteroid[i].texture = asteroid_texture;
		game.asteroid[i].radius = asteroid_texture.height / 2.0f;
		i++;
	}
	UnloadImage(image);
}

void textureUnload()
{
	UnloadTexture(game.planet.texture);
	UnloadTexture(game.asteroid[0].texture);
	UnloadTexture(game.asteroid[1].texture);
	UnloadTexture(game.asteroid[2].texture);
	UnloadTexture(game.asteroid[3].texture);
	UnloadTexture(game.asteroid[4].texture);
	UnloadTexture(game.shield.texture);
}

int main(void)
{
	srand(time(NULL));
	const int   screenWidth = 1000;
    const int   screenHeight = 1000;
	InitWindow(screenWidth, screenHeight, "Planet Guardian");

	game.cold.interval = 0.15f;
	game.shadow.interval = 0.15f;

	textureLoader();

	SetTargetFPS(60);
	game.planet.pos.x = (screenWidth - game.planet.texture.width) / 2.0f;
	game.planet.pos.y = (screenHeight - game.planet.texture.height) / 2.0f;
	game.planet.center_pos.x = game.planet.pos.x + game.planet.texture.width / 2.0f;
	game.planet.center_pos.y = game.planet.pos.y + game.planet.texture.width / 2.0f;
	// Aim to the middle of the planet
	// calculating the target to the middle

	initialize_all_asteroids();
	float shieldAngle = 0.0f;
	int shieldDirection = 1;
	while (!WindowShouldClose())
	{


        // --- Calculate Shield Collision Circles ---
        float orbitRadius = game.planet.radius + 50.0f;
        Vector2 planetCenter = game.planet.center_pos;
        Vector2 shieldMidPoint = {
            planetCenter.x + cosf(shieldAngle) * orbitRadius,
            planetCenter.y + sinf(shieldAngle) * orbitRadius
        };
        Vector2 tangentDir = {-sinf(shieldAngle), cosf(shieldAngle)};

        // --- Shield Circle Parameters (TUNABLE) ---
        float shieldSegmentOffset = game.shield.texture.width * 0.4f;
        float shieldSegmentRadius = game.shield.texture.width * 0.15;
        Vector2 shieldCircle1Center = Vector2Add(shieldMidPoint, Vector2Scale(tangentDir, shieldSegmentOffset));
		Vector2 shieldCircle2Center = Vector2Add(shieldMidPoint, Vector2Scale(tangentDir, -shieldSegmentOffset));
		shieldSegmentRadius = game.shield.texture.width * 0.093f;
        Vector2 shieldCircle3Center = Vector2Add(shieldMidPoint, Vector2Scale(tangentDir, -shieldSegmentOffset * 0.2));
		Vector2 shieldCircle4Center = Vector2Add(shieldMidPoint, Vector2Scale(tangentDir, shieldSegmentOffset * 0.2));
        shieldSegmentRadius = game.shield.texture.width * 0.12f;
        Vector2 shieldCircle5Center = Vector2Add(shieldMidPoint, Vector2Scale(tangentDir, -shieldSegmentOffset * 0.7));
		Vector2 shieldCircle6Center = Vector2Add(shieldMidPoint, Vector2Scale(tangentDir, shieldSegmentOffset * 0.7));


		if (IsKeyPressed(KEY_SPACE))
        		shieldDirection = -shieldDirection;
        	float deltaTime = GetFrameTime();
		shieldAngle += deltaTime * 3.0f * shieldDirection; // Get time elapsed since last frame
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
				game.asteroid[i] = initialize_asteroid(game.asteroid[i]);
			game.asteroid[i].pos = moveTowardsWithGravity(game.asteroid[i].pos, game.planet.center_pos, game.asteroid[i].speed, game.planet.center_pos);

			if (CheckCollisionCircles(game.asteroid[i].center_pos, game.asteroid[i].radius, shieldCircle1Center, shieldSegmentRadius) ||
			CheckCollisionCircles(game.asteroid[i].center_pos, game.asteroid[i].radius, shieldCircle2Center, shieldSegmentRadius) ||
			CheckCollisionCircles(game.asteroid[i].center_pos, game.asteroid[i].radius, shieldCircle3Center, shieldSegmentRadius)||
			CheckCollisionCircles(game.asteroid[i].center_pos, game.asteroid[i].radius, shieldCircle4Center, shieldSegmentRadius)||
			CheckCollisionCircles(game.asteroid[i].center_pos, game.asteroid[i].radius, shieldCircle5Center, shieldSegmentRadius)||
			CheckCollisionCircles(game.asteroid[i].center_pos, game.asteroid[i].radius, shieldCircle6Center, shieldSegmentRadius))
			{
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



			DrawTexturePro(game.background, (Rectangle){.x = 0, .y = 0,
					.width = game.background.width, .height = game.background.height},
				(Rectangle){.x = game.background.width, .y = game.background.height,
					.width = screenWidth, .height = screenHeight},
				(Vector2){.x = game.background.width, .y = game.background.height},
				0,
				WHITE);

			update_planet_condition(deltaTime);
			DrawTextureV(game.planet.texture, game.planet.pos, WHITE);
			DrawTextureV(game.cold.texture, game.planet.pos,
				(Color){.r = 255, .g = 255, .b = 255, .a = game.cold.value});

			DrawTexturePro(game.shadow.texture,
				(Rectangle){.x = 0, .y = 0,
					.height = game.shadow.texture.height, .width = game.shadow.texture.width},
				(Rectangle){.x = screenWidth / 2, .y = screenHeight / 2,
					.height = game.shadow.texture.height, .width = game.shadow.texture.width},
				(Vector2){.x = game.planet.texture.width / 2, .y = game.planet.texture.height / 2},
				game.shadow.rotation,
				(Color){.r = 0, .g = 0, .b = 0, .a = 150});
			draw_shield(shieldAngle);
			//debugging shield
			// DrawCircleLinesV(shieldCircle1Center, game.shield.texture.width * 0.093f, BLACK);
			// DrawCircleLinesV(shieldCircle2Center, game.shield.texture.width * 0.093f, BLACK);
			// DrawCircleLinesV(shieldCircle3Center, game.shield.texture.width * 0.15f, BLACK);
			// DrawCircleLinesV(shieldCircle4Center, game.shield.texture.width * 0.15f, BLACK);
			// DrawCircleLinesV(shieldCircle5Center, game.shield.texture.width * 0.12f, BLACK);
			// DrawCircleLinesV(shieldCircle6Center, game.shield.texture.width * 0.12f, BLACK);
			draw_asteroids();
			printp("HEALTH: 3", 550., 750., 1.0f, RED);
		EndDrawing();
	}

	textureUnload();
	CloseWindow();

	return (EXIT_SUCCESS);
}
