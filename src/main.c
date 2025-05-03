#include "planet_guardian.h"

game_t game;



void textureLoader()
{
	Image image = LoadImage("assets/graphics/icon.png");
	Texture2D texture = LoadTextureFromImage(image);
	game.planet.texture = texture;
	game.planet.radius = texture.height / 2.0f;
	UnloadImage(image);
	image = LoadImage("assets/graphics/ROCK.png");
	Texture2D texture1 = LoadTextureFromImage(image);
	game.asteroid[0].texture = texture1;
	UnloadImage(image);
	image = LoadImage("assets/graphics/ROCK.png");
	Texture2D texture2 = LoadTextureFromImage(image);
	game.asteroid[1].texture = texture2;
	game.asteroid[1].radius = texture2.height / 2.0f;
	UnloadImage(image);
	image = LoadImage("assets/graphics/ROCK.png");
	Texture2D texture3 = LoadTextureFromImage(image);
	game.asteroid[2].texture = texture3;
	game.asteroid[2].radius = texture3.height / 2.0f;
	UnloadImage(image);
	image = LoadImage("assets/graphics/ROCK.png");
	Texture2D texture4 = LoadTextureFromImage(image);
	game.asteroid[3].texture = texture4;
	game.asteroid[3].radius = texture3.height / 2.0f;
	UnloadImage(image);
	image = LoadImage("assets/graphics/ROCK.png");
	Texture2D texture5 = LoadTextureFromImage(image);
	game.asteroid[4].texture = texture5;
	game.asteroid[4].radius = texture4.height / 2.0f;
	UnloadImage(image);
	image = LoadImage("assets/graphics/shield.png");
	Texture2D texture6 = LoadTextureFromImage(image);
	game.shield.texture = texture6;
	game.shield.radius = texture6.height / 2.0f;

// TEST
	int i = 0;
	image = LoadImage("assets/graphics/ROCK.png");
	Texture2D asteroid_texture = LoadTextureFromImage(image);
	while (i < MAX_ASTEROIDS)
	{
		game.asteroid[i].texture = asteroid_texture;
		game.asteroid[i].radius = texture4.height / 2.0f;
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
	float shieldAngle = 0.0f;
	srand(time(NULL));
	const int   screenWidth = 800;
    const int   screenHeight = 800;
	InitWindow(screenWidth, screenHeight, "Jam!");

	textureLoader();

	SetTargetFPS(60);    
	game.planet.pos.x = (screenWidth - game.planet.texture.width) / 2.0f;
	game.planet.pos.y = (screenHeight - game.planet.texture.height) / 2.0f;
	game.planet.center_pos.x = game.planet.pos.x + game.planet.texture.width / 2.0f;
	game.planet.center_pos.y = game.planet.pos.y + game.planet.texture.width / 2.0f;
	// Aim to the middle of the planet
	// calculating the target to the middle

	initialize_all_asteroids();
	
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


		float deltaTime = GetFrameTime();
		if (IsKeyDown(KEY_SPACE))
			shieldAngle += deltaTime * 3.0f;  // Get time elapsed since last frame
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
				game.asteroid[i].pos = generateAsteroidPos();
			game.asteroid[i].pos = moveTowardsWithGravity(game.asteroid[i].pos, game.planet.center_pos, game.asteroid[i].speed, game.planet.center_pos);

			if (CheckCollisionCircles(game.asteroid[i].center_pos, game.asteroid[i].radius, shieldCircle1Center, shieldSegmentRadius) ||
			CheckCollisionCircles(game.asteroid[i].center_pos, game.asteroid[i].radius, shieldCircle2Center, shieldSegmentRadius) ||
			CheckCollisionCircles(game.asteroid[i].center_pos, game.asteroid[i].radius, shieldCircle3Center, shieldSegmentRadius)||
			CheckCollisionCircles(game.asteroid[i].center_pos, game.asteroid[i].radius, shieldCircle4Center, shieldSegmentRadius)||
			CheckCollisionCircles(game.asteroid[i].center_pos, game.asteroid[i].radius, shieldCircle5Center, shieldSegmentRadius)||
			CheckCollisionCircles(game.asteroid[i].center_pos, game.asteroid[i].radius, shieldCircle6Center, shieldSegmentRadius))
			{
				 game.asteroid[i].pos = generateAsteroidPos();
			}
			i++;
		}

			// float deltaTime = GetFrameTime();  // Get time elapsed since last frame
			// totalTime += deltaTime;

		BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawCircle(game.planet.center_pos.x, game.planet.center_pos.y, game.planet.radius, RED);
			DrawTextureV(game.planet.texture, game.planet.pos, WHITE);
			draw_shield(shieldAngle);
			// shieldSegmentOffset = game.shield.texture.width * 0.4f; debugging
			// shieldSegmentRadius = game.shield.texture.width * 0.093f;
			// DrawCircleLinesV(shieldCircle1Center, shieldSegmentRadius, GREEN);
			// DrawCircleLinesV(shieldCircle2Center, shieldSegmentRadius, GREEN);
			// shieldSegmentRadius = game.shield.texture.width * 0.15f;
			// DrawCircleLinesV(shieldCircle3Center, shieldSegmentRadius, GREEN);
			// DrawCircleLinesV(shieldCircle4Center, shieldSegmentRadius, GREEN);
			// shieldSegmentRadius = game.shield.texture.width * 0.12f;
			// DrawCircleLinesV(shieldCircle5Center, shieldSegmentRadius, GREEN);
			// DrawCircleLinesV(shieldCircle6Center, shieldSegmentRadius, GREEN);
			draw_asteroids();
		EndDrawing();
	}

	textureUnload();
	CloseWindow();

	return (EXIT_SUCCESS);
}
