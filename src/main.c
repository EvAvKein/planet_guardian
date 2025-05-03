#include "planet_guardian.h"

game_t game;

void textureLoader()
{
	Image image = LoadImage("assets/graphics/icon.png");
	Texture2D texture = LoadTextureFromImage(image);
	game.planet.texture = texture;
	game.planet.radius = texture.height;
	UnloadImage(image);
	image = LoadImage("assets/graphics/ROCK.png");
	Texture2D texture1 = LoadTextureFromImage(image);
	game.asteroid[0].texture = texture1;
	game.asteroid[0].radius = texture1.height;
	UnloadImage(image);
	image = LoadImage("assets/graphics/ROCK.png");
	Texture2D texture2 = LoadTextureFromImage(image);
	game.asteroid[1].texture = texture2;
	game.asteroid[1].radius = texture2.height;
	UnloadImage(image);
	image = LoadImage("assets/graphics/ROCK.png");
	Texture2D texture3 = LoadTextureFromImage(image);
	game.asteroid[2].texture = texture3;
	game.asteroid[2].radius = texture3.height;
	UnloadImage(image);
	image = LoadImage("assets/graphics/ROCK.png");
	Texture2D texture4 = LoadTextureFromImage(image);
	game.asteroid[3].texture = texture4;
	game.asteroid[3].radius = texture3.height;
	UnloadImage(image);
	image = LoadImage("assets/graphics/ROCK.png");
	Texture2D texture5 = LoadTextureFromImage(image);
	game.asteroid[4].texture = texture5;
	game.asteroid[4].radius = texture4.height;
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
	int x = (screenWidth - game.planet.texture.width) / 2;
	int y = (screenHeight - game.planet.texture.height) / 2;
	Vector2	planetpos = {x, y};
	float	planet_radius = 85.0f;
	// Aim to the middle of the planet
	// calculating the target to the middle
	Vector2 target = 
	{
		x + game.planet.texture.width / 2.0f,
		y + game.planet.texture.height / 2.0f
	};

	game.asteroid[0].speed = 1;
	game.asteroid[1].speed = 1;
	game.asteroid[2].speed = 1;
	game.asteroid[3].speed = 1;
	game.asteroid[4].speed = 1;

	int	asteroid_radius = 10;
	Vector2 position1 = generateAsteroidPos();
	Vector2 position2 = generateAsteroidPos();
	Vector2 position3 = generateAsteroidPos();
	Vector2 position4 = generateAsteroidPos();
	Vector2 position5 = generateAsteroidPos();

	game.asteroid[0].direction = generateRandomDir(game.asteroid[0].pos);
	game.asteroid[1].direction = generateRandomDir(game.asteroid[1].pos);
	game.asteroid[2].direction = generateRandomDir(game.asteroid[2].pos);
	game.asteroid[3].direction = generateRandomDir(game.asteroid[3].pos);
	game.asteroid[4].direction = generateRandomDir(game.asteroid[4].pos);

	Vector2 asteroid1_center = { position1.x - asteroid_radius, position1.y - asteroid_radius};
	Vector2 asteroid2_center = { position2.x - asteroid_radius, position2.y - asteroid_radius};
	Vector2 asteroid3_center = { position3.x - asteroid_radius, position3.y - asteroid_radius};
	Vector2 asteroid4_center = { position4.x - asteroid_radius, position4.y - asteroid_radius};
	Vector2 asteroid5_center = { position5.x - asteroid_radius, position5.y - asteroid_radius};

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
		angle += 0.01f; // Adjust the speed of rotation here
		if (CheckCollisionCircles(target, planet_radius, asteroid1_center, asteroid_radius))
		    position1 = generateAsteroidPos();
		if (CheckCollisionCircles(target, planet_radius, asteroid2_center, asteroid_radius))
		    position2 = generateAsteroidPos();
		if (CheckCollisionCircles(target, planet_radius, asteroid3_center, asteroid_radius))
		    position3 = generateAsteroidPos();
		if (CheckCollisionCircles(target, planet_radius, asteroid4_center, asteroid_radius))
		    position4 = generateAsteroidPos();
		if (CheckCollisionCircles(target, planet_radius, asteroid5_center, asteroid_radius))
		    position5 = generateAsteroidPos();

		float deltaTime = GetFrameTime();  // Get time elapsed since last frame
		totalTime += deltaTime;

		 // Calculate the new position of the rotating image based on the angle
		 float x = planetPosition.x + rotationRadius * cos(angle);
		 float y = planetPosition.y + rotationRadius * sin(angle);


		BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawCircle(target.x, target.y, planet_radius, RED);
			DrawTextureV(game.planet.texture, planetpos, WHITE);
			DrawTextureV(game.asteroid[0].texture, position1, WHITE);
			if (totalTime > spawnDelay)
				DrawTextureV(game.asteroid[1].texture, position2, WHITE);
			if (totalTime > spawnDelay * 2)
				DrawTextureV(game.asteroid[2].texture, position3, WHITE);
			if (totalTime > spawnDelay * 3)
				DrawTextureV(game.asteroid[3].texture, position4, WHITE);
			if (totalTime > spawnDelay * 4)
				DrawTextureV(game.asteroid[4].texture, position5, WHITE);
			DrawTextureEx(rotatingImage, (Vector2){x - rotatingImage.width / 2.0f, y - rotatingImage.height / 2.0f}, angle * 180.0f / PI, 1.0f, WHITE);
		EndDrawing();
		position1 = moveTowardsWithGravity(position1, game.asteroid[0].direction, game.asteroid[0].speed, game.planet.center_pos);
		if (totalTime > spawnDelay)
			position2 = moveTowardsWithGravity(position2, game.asteroid[1].direction, game.asteroid[1].speed, game.planet.center_pos);
		if (totalTime > spawnDelay * 2)
			position3 = moveTowardsWithGravity(position3, game.asteroid[2].direction, game.asteroid[2].speed, game.planet.center_pos);
		if (totalTime > spawnDelay * 3)
			position4 = moveTowardsWithGravity(position4, game.asteroid[3].direction, game.asteroid[3].speed, game.planet.center_pos);
		if (totalTime > spawnDelay * 4)
			position5 = moveTowardsWithGravity(position5, game.asteroid[4].direction, game.asteroid[4].speed, game.planet.center_pos);

		asteroid1_center.x = position1.x + asteroid_radius;
		asteroid1_center.y = position1.y + asteroid_radius;

		asteroid2_center.x = position2.x + asteroid_radius;
		asteroid2_center.y = position2.y + asteroid_radius;

		asteroid3_center.x = position3.x + asteroid_radius;
		asteroid3_center.y = position3.y + asteroid_radius;

		asteroid4_center.x = position4.x + asteroid_radius;
		asteroid4_center.y = position4.y + asteroid_radius;

		asteroid5_center.x = position5.x + asteroid_radius;
		asteroid5_center.y = position5.y + asteroid_radius;
	}

	textureUnload();
	CloseWindow();

	return (EXIT_SUCCESS);
}
