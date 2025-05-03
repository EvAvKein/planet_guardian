#include "planet_guardian.h"
#include "raylib.h"
#include <stdlib.h>

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
	game.asteroid[0].radius = texture1.height / 2.0f;
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

Vector2 moveTowards(Vector2 current, Vector2 target, float speed)
{

	Vector2 direction = Vector2Subtract(target, current);
    float distance = Vector2Length(direction);

	if (distance <= speed || distance == 0.0f) return target;

    direction = Vector2Scale(Vector2Normalize(direction), speed);
    return Vector2Add(current, direction);
}


Vector2 generateAsteroidPos()
{
    int edge = rand() % 4;
    Vector2 position;

    switch (edge)
    {
        case 0:
            position.x = (float)(rand() % GetScreenWidth());
            position.y = -50;
            break;
        case 1:
            position.x = GetScreenWidth() + 50;
            position.y = (float)(rand() % GetScreenHeight());
            break;
        case 2:
            position.x = (float)(rand() % GetScreenWidth());
            position.y = GetScreenHeight() + 50;
            break;
        case 3:
            position.x = -50;
            position.y = (float)(rand() % GetScreenHeight());
            break;
    }

    return position;
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

	game.asteroid[0].pos = generateAsteroidPos();
	game.asteroid[1].pos = generateAsteroidPos();
	game.asteroid[2].pos = generateAsteroidPos();
	game.asteroid[3].pos = generateAsteroidPos();
	game.asteroid[4].pos = generateAsteroidPos();

	game.asteroid[0].speed = rand() % 5;

	float spawnDelay = 3.0f;  // Delay in seconds before spawning new asteroid
	float totalTime = 0.0f;  // Total elapsed time

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
		game.asteroid[0].pos = moveTowards(game.asteroid[0].pos, game.planet.center_pos, game.asteroid[0].speed);
		if (totalTime > spawnDelay)
			game.asteroid[1].pos = moveTowards(game.asteroid[1].pos, game.planet.center_pos, game.asteroid[0].speed);
		if (totalTime > spawnDelay * 2)
			game.asteroid[2].pos = moveTowards(game.asteroid[2].pos, game.planet.center_pos, game.asteroid[0].speed);
		if (totalTime > spawnDelay * 3)
			game.asteroid[3].pos = moveTowards(game.asteroid[3].pos, game.planet.center_pos, game.asteroid[0].speed);
		if (totalTime > spawnDelay * 4)
			game.asteroid[4].pos = moveTowards(game.asteroid[4].pos, game.planet.center_pos, game.asteroid[0].speed);

	}

	textureUnload();
	CloseWindow();

	return (EXIT_SUCCESS);
}
