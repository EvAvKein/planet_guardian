#include "planet_guardian.h"

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
	image = LoadImage("assets/graphics/shield.png");
	Texture2D texture6 = LoadTextureFromImage(image);
	game.shield.sprite.texture = texture6;
	game.shield.sprite.radius = texture6.height / 2.0f;

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
	UnloadTexture(game.shield.sprite.texture);
}
