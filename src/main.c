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
}

void textureUnload()
{
	UnloadTexture(game.planet.texture);
	UnloadTexture(game.asteroid[0].texture);
	UnloadTexture(game.asteroid[1].texture);
	UnloadTexture(game.asteroid[2].texture);
	UnloadTexture(game.asteroid[3].texture);
	UnloadTexture(game.asteroid[4].texture);
}

int main(void)
{
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

	// Initialize asteroids
	initialize_all_asteroids();
	
	float spawnDelay = 3.0f;  // Delay in seconds before spawning new asteroid
	float totalTime = 0.0f;  // Total elapsed time

	Image image = LoadImage("assets/graphics/shield.png");
	Texture2D rotatingImage = LoadTextureFromImage(image); // Replace with your image
    Vector2 planetPosition = { screenWidth / 2.0f, screenHeight / 2.0f }; // Position of the planet
    float rotationRadius = 150.0f; // Radius of the circular orbit around the planet

    // Variable to control the rotation angle (in radians)
    float angle = 0.0f;

	while (!WindowShouldClose())
	{
		game.asteroid[0].center_pos.x = game.asteroid[0].pos.x + game.asteroid[0].radius;
		game.asteroid[0].center_pos.y = game.asteroid[0].pos.y + game.asteroid[0].radius;
		game.asteroid[1].center_pos.x = game.asteroid[1].pos.x + game.asteroid[1].radius;
		game.asteroid[1].center_pos.y = game.asteroid[1].pos.y + game.asteroid[1].radius;
		game.asteroid[2].center_pos.x = game.asteroid[2].pos.x + game.asteroid[2].radius;
		game.asteroid[2].center_pos.y = game.asteroid[2].pos.y + game.asteroid[2].radius;
		game.asteroid[3].center_pos.x = game.asteroid[3].pos.x + game.asteroid[3].radius;
		game.asteroid[3].center_pos.y = game.asteroid[3].pos.y + game.asteroid[3].radius;
		game.asteroid[4].center_pos.x = game.asteroid[4].pos.x + game.asteroid[4].radius;
		game.asteroid[4].center_pos.y = game.asteroid[4].pos.y + game.asteroid[4].radius;

		if (CheckCollisionCircles(game.planet.center_pos, game.planet.radius, game.asteroid[0].center_pos, game.asteroid[0].radius))
		    game.asteroid[0].pos = generateAsteroidPos();
		if (CheckCollisionCircles(game.planet.center_pos, game.planet.radius, game.asteroid[1].center_pos, game.asteroid[1].radius))
		    game.asteroid[1].pos = generateAsteroidPos();
		if (CheckCollisionCircles(game.planet.center_pos, game.planet.radius, game.asteroid[2].center_pos, game.asteroid[2].radius))
		    game.asteroid[2].pos = generateAsteroidPos();
		if (CheckCollisionCircles(game.planet.center_pos, game.planet.radius, game.asteroid[3].center_pos, game.asteroid[3].radius))
		    game.asteroid[3].pos = generateAsteroidPos();
		if (CheckCollisionCircles(game.planet.center_pos, game.planet.radius, game.asteroid[4].center_pos, game.asteroid[4].radius))
		    game.asteroid[4].pos = generateAsteroidPos();

		float deltaTime = GetFrameTime();  // Get time elapsed since last frame
		totalTime += deltaTime;

		 // Calculate the new position of the rotating image based on the angle
		 float x = planetPosition.x + rotationRadius * cos(angle);
		 float y = planetPosition.y + rotationRadius * sin(angle);


		BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawCircle(game.planet.center_pos.x, game.planet.center_pos.y, game.planet.radius, RED);
			DrawTextureV(game.planet.texture, game.planet.pos, WHITE);
			DrawTextureV(game.asteroid[0].texture, game.asteroid[0].pos, WHITE);
			if (totalTime > spawnDelay)
				DrawTextureV(game.asteroid[1].texture, game.asteroid[1].pos, WHITE);
			if (totalTime > spawnDelay * 2)
				DrawTextureV(game.asteroid[2].texture, game.asteroid[2].pos, WHITE);
			if (totalTime > spawnDelay * 3)
				DrawTextureV(game.asteroid[3].texture, game.asteroid[3].pos, WHITE);
			if (totalTime > spawnDelay * 4)
				DrawTextureV(game.asteroid[4].texture, game.asteroid[4].pos, WHITE);
		EndDrawing();
		game.asteroid[0].pos = moveTowardsWithGravity(game.asteroid[0].pos, game.planet.center_pos, game.asteroid[0].speed);
		if (totalTime > spawnDelay)
			game.asteroid[1].pos = moveTowardsWithGravity(game.asteroid[1].pos, game.planet.center_pos, game.asteroid[0].speed);
		if (totalTime > spawnDelay * 2)
			game.asteroid[2].pos = moveTowardsWithGravity(game.asteroid[2].pos, game.planet.center_pos, game.asteroid[0].speed);
		if (totalTime > spawnDelay * 3)
			game.asteroid[3].pos = moveTowardsWithGravity(game.asteroid[3].pos, game.planet.center_pos, game.asteroid[0].speed);
		if (totalTime > spawnDelay * 4)
			game.asteroid[4].pos = moveTowardsWithGravity(game.asteroid[4].pos, game.planet.center_pos, game.asteroid[0].speed);

	}

	textureUnload();
	CloseWindow();

	return (EXIT_SUCCESS);
}
