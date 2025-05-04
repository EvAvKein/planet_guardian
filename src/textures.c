#include "planet_guardian.h"

void textureLoader()
{
	game.font = LoadFontEx("assets/fonts/PIXY.ttf", 32, 0, 250);
	game.planet.texture = LoadTexture("assets/graphics/earth_normal.png");
	game.planet.radius = game.planet.texture.height / 2.0f;
	game.temp.hot_texture = LoadTexture("assets/graphics/earth_dry.png");
	game.temp.cold_texture = LoadTexture("assets/graphics/earth_snow.png");
	Image shadow_image = LoadImage("assets/graphics/earth_normal.png");
	ImageCrop(&shadow_image, (Rectangle){
		.height = shadow_image.height, .width = shadow_image.width / 2});
	game.shadow.texture = LoadTextureFromImage(shadow_image);
	UnloadImage(shadow_image);
	game.background = LoadTexture("assets/graphics/background_1-64x64.png");
	game.shield.sprite.texture = LoadTexture("assets/graphics/shield.png");
	game.shield.sprite.radius = game.shield.sprite.texture.height / 2.0f;
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
}

void textureUnload()
{
	UnloadTexture(game.planet.texture);
	UnloadTexture(game.temp.hot_texture);
	UnloadTexture(game.temp.cold_texture);
	int i = 0;
	while (i < MAX_ASTEROIDS)
	{
		UnloadTexture(game.asteroid[i].texture);
	}
	UnloadTexture(game.shield.sprite.texture);
	
	// Do we need to unload textures on the individual asteroids in the array,
	// or is just these four enough?
	//
	// UnloadTexture(game.asteroid_textures[0]);
	// UnloadTexture(game.asteroid_textures[1]);
	// UnloadTexture(game.asteroid_textures[2]);
	// UnloadTexture(game.asteroid_textures[3]);
}
