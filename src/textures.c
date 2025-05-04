#include "planet_guardian.h"
#include "raylib.h"

void textureLoader()
{
	Image	asteroid_images[MAX_ASTEROIDS];
	//char	*asteroid_assets[4];
	float	bg_scale = 4;

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
	Image bg_image = LoadImage("assets/graphics/background_2-64x64.png");
	ImageResize(&bg_image, bg_image.width * bg_scale, bg_image.height * bg_scale);
	game.background = LoadTextureFromImage(bg_image);
	game.shield.sprite.texture = LoadTexture("assets/graphics/shield.png");
	game.shield.sprite.radius = game.shield.sprite.texture.height / 2.0f;
	game.logo = LoadTexture("assets/graphics/logo_transparent.png");
	game.menu = LoadTexture("assets/graphics/menu_background.png");
	game.asteroid_textures[0] = "assets/graphics/asteroid.png";
	game.asteroid_textures[1] = "assets/graphics/asteroid2.png";
	game.asteroid_textures[2] = "assets/graphics/asteroid3.png";
	game.asteroid_textures[3] = "assets/graphics/asteroid4.png";
	// asteroid_assets[0] = "assets/graphics/asteroid.png";	
	// asteroid_assets[1] = "assets/graphics/asteroid2.png";	
	// asteroid_assets[2] = "assets/graphics/asteroid3.png";	
	// asteroid_assets[3] = "assets/graphics/asteroid4.png";	
	int i = 0;
	Texture2D asteroid_texture;
	while (i < MAX_ASTEROIDS)
	{
		asteroid_images[i] = LoadImage(random_asteroid_texture()); 
		float scale = GetRandomValue(3, 10) * 0.1f;
		ImageResize(&asteroid_images[i], asteroid_images[i].width * scale, asteroid_images[i].height * scale);
		asteroid_texture = LoadTextureFromImage(asteroid_images[i]);
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
		++i;
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
