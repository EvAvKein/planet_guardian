#include "planet_guardian.h"
#include "raylib.h"

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
	float speed = 1.5f;

	int	asteroid_radius = 10;
	Vector2 position1 = generateAsteroidPos();
	Vector2 position2 = generateAsteroidPos();
	Vector2 position3 = generateAsteroidPos();
	Vector2 position4 = generateAsteroidPos();
	Vector2 position5 = generateAsteroidPos();

	Vector2 asteroid1_center = { position1.x - asteroid_radius, position1.y - asteroid_radius};
	Vector2 asteroid2_center = { position2.x - asteroid_radius, position2.y - asteroid_radius};
	Vector2 asteroid3_center = { position3.x - asteroid_radius, position3.y - asteroid_radius};
	Vector2 asteroid4_center = { position4.x - asteroid_radius, position4.y - asteroid_radius};
	Vector2 asteroid5_center = { position5.x - asteroid_radius, position5.y - asteroid_radius};

	while (!WindowShouldClose())
	{
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
		BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawCircle(target.x, target.y, planet_radius, RED);
			DrawTextureV(game.planet.texture, planetpos, WHITE);
			DrawTextureV(game.asteroid[0].texture, position1, WHITE);
			DrawTextureV(game.asteroid[1].texture, position2, WHITE);
			DrawTextureV(game.asteroid[2].texture, position3, WHITE);
			DrawTextureV(game.asteroid[3].texture, position4, WHITE);
			DrawTextureV(game.asteroid[4].texture, position5, WHITE);
		EndDrawing();
		position1 = moveTowards(position1, target, speed);
		position2 = moveTowards(position2, target, speed);
		position3 = moveTowards(position3, target, speed);
		position4 = moveTowards(position4, target, speed);
		position5 = moveTowards(position5, target, speed);

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
