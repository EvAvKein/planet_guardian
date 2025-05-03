#include "planet_guardian.h"

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
		asteroid.direction = game.planet.center_pos;
		asteroid.speed = fmod(rand(), MAX_ASTEROID_SPEED);
		// CHANGE IF NEEDED THE DIRECTION
		asteroid.radius = asteroid.texture.width / 2.0f;
	return (asteroid);
}

Vector2 get_center_pos(sprite_t sprite)
{
	sprite.center_pos.x = sprite.pos.x + sprite.texture.width / 2.0f;
	sprite.center_pos.y = sprite.pos.y + sprite.texture.width / 2.0f;
	return (sprite.center_pos);
}
