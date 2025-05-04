#include "planet_guardian.h"

void textureLoader()
{
	Image image = LoadImage("assets/graphics/earth_normal.png");
	game.font = LoadFontEx("assets/fonts/PIXY.ttf", 32, 0, 250);
	Texture2D texture = LoadTextureFromImage(image);
	game.planet.texture = texture;
	game.planet.radius = texture.height / 2.0f;
	UnloadImage(image);
	game.temp.hot_texture = LoadTexture("assets/graphics/earth_dry.png");
	game.temp.cold_texture = LoadTexture("assets/graphics/earth_snow.png");
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
	game.logo = LoadTexture("assets/graphics/logo_transparent.png");
	game.menu = LoadTexture("assets/graphics/menu_background.png");
	game.asteroid_textures[0] = LoadTexture("assets/graphics/asteroid.png");	
	game.asteroid_textures[1] = LoadTexture("assets/graphics/asteroid2.png");	
	game.asteroid_textures[2] = LoadTexture("assets/graphics/asteroid3.png");	
	game.asteroid_textures[3] = LoadTexture("assets/graphics/asteroid4.png");	
	int i = 0;
	Texture2D asteroid_texture;
	while (i < MAX_ASTEROIDS)
	{
		asteroid_texture = random_asteroid_texture();
		game.asteroid[i].texture = asteroid_texture;
		game.asteroid[i].radius = asteroid_texture.height / 2.0f;
		i++;
	}
	UnloadImage(image);
}

void textureUnload()
{
	UnloadTexture(game.planet.texture);
	int i = 0;
	while (i < MAX_ASTEROIDS)
	{
		UnloadTexture(game.asteroid[i].texture);
	}
	UnloadTexture(game.temp.hot_texture);
	UnloadTexture(game.temp.cold_texture);
	UnloadTexture(game.shield.sprite.texture);
}
