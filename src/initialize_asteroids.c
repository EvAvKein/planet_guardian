#include "planet_guardian.h"
#include "raylib.h"

char	 *random_asteroid_texture()
{
	return game.asteroid_textures[rand() % 4];
}

void initialize_all_asteroids()
{
	int	i;

	i = 0;
	while (i < MAX_ASTEROIDS)
	{
		game.asteroid[i] = initialize_asteroid(game.asteroid[i]);
		i++;
	}
}

sprite_t initialize_asteroid(sprite_t asteroid)
{
		asteroid.is_inside_screen = false;
		asteroid.pos = generateAsteroidPos();
		asteroid.center_pos = get_center_pos(asteroid);
		// CHANGE THE DIRECTION
		asteroid.direction = generateRandomDir(asteroid.pos);
		asteroid.speed = GetRandomValue(MIN_ASTEROID_SPEED, MAX_ASTEROID_SPEED) * 0.01f;
		// CHANGE IF NEEDED THE DIRECTION
		asteroid.radius = asteroid.texture.width / 2.0f;
		Image asteroid_image = LoadImage(random_asteroid_texture()); 
		float scale = GetRandomValue(MIN_ASTEROID_RADIUS, MAX_ASTEROID_RADIUS) * 0.1f;
		ImageResize(&asteroid_image, asteroid_image.width * scale, asteroid_image.height * scale);
		Texture2D asteroid_texture = LoadTextureFromImage(asteroid_image);
		asteroid.texture = asteroid_texture;
		asteroid.radius = asteroid_texture.height / 2.0f;
		//asteroid.texture = random_asteroid_texture();
	return (asteroid);

}

Vector2 get_center_pos(sprite_t sprite)
{
	sprite.center_pos.x = sprite.pos.x + sprite.texture.width / 2.0f;
	sprite.center_pos.y = sprite.pos.y + sprite.texture.width / 2.0f;
	return (sprite.center_pos);
}
