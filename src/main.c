#include "planet_guardian.h"

game_t game;

void textureLoader()
{
	Image image = LoadImage("assets/graphics/icon.png");
	Texture2D texture = LoadTextureFromImage(image);
	game.planet = texture;
	UnloadImage(image);
	image = LoadImage("assets/graphics/ROCK.png");
	Texture2D texture1 = LoadTextureFromImage(image);
	game.asteroid[0] = texture1;
	UnloadImage(image);
	image = LoadImage("assets/graphics/ROCK.png");
	Texture2D texture2 = LoadTextureFromImage(image);
	game.asteroid[1] = texture2;
	UnloadImage(image);
	image = LoadImage("assets/graphics/ROCK.png");
	Texture2D texture3 = LoadTextureFromImage(image);
	game.asteroid[2] = texture3;
	UnloadImage(image);
	image = LoadImage("assets/graphics/ROCK.png");
	Texture2D texture4 = LoadTextureFromImage(image);
	game.asteroid[3] = texture4;
	UnloadImage(image);
	image = LoadImage("assets/graphics/ROCK.png");
	Texture2D texture5 = LoadTextureFromImage(image);
	game.asteroid[4] = texture5;
	UnloadImage(image);
}

void textureUnload()
{
	UnloadTexture(game.planet);
	UnloadTexture(game.asteroid[0]);
	UnloadTexture(game.asteroid[1]);
	UnloadTexture(game.asteroid[2]);
	UnloadTexture(game.asteroid[3]);
	UnloadTexture(game.asteroid[4]);
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
	const int screenWidth = 800;
    const int screenHeight = 800;
	InitWindow(screenWidth, screenHeight, "Jam!");

	textureLoader();

	SetTargetFPS(60);    
	int x = (screenWidth - game.planet.width) / 2;
	int y = (screenHeight - game.planet.height) / 2;
	Vector2 planetpos = {x, y};
	// Aim to the middle of the planet
	// calculating the target to the middle
	Vector2 target = 
	{
		x + game.planet.width / 2.0f,
		y + game.planet.height / 2.0f
	};
	float speed = 0.5f;

	Vector2 position1 = generateAsteroidPos();
	Vector2 position2 = generateAsteroidPos();
	Vector2 position3 = generateAsteroidPos();
	Vector2 position4 = generateAsteroidPos();
	Vector2 position5 = generateAsteroidPos();

	while (!WindowShouldClose())
	{
		BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawTextureV(game.planet, planetpos, WHITE);
			DrawTextureV(game.asteroid[0], position1, WHITE);
			DrawTextureV(game.asteroid[1], position2, WHITE);
			DrawTextureV(game.asteroid[2], position3, WHITE);
			DrawTextureV(game.asteroid[3], position4, WHITE);
			DrawTextureV(game.asteroid[4], position5, WHITE);
		EndDrawing();
		position1 = moveTowards(position1, target, speed);
		position2 = moveTowards(position2, target, speed);
		position3 = moveTowards(position3, target, speed);
		position4 = moveTowards(position4, target, speed);
		position5 = moveTowards(position5, target, speed);
	}

	textureUnload();
	CloseWindow();

	return (EXIT_SUCCESS);
}
