#include "planet_guardian.h"

bool check_collision(sprite_t sprite_a, sprite_t sprite_b)
{
	if (CheckCollisionCircles(sprite_a.center_pos, sprite_a.radius, sprite_b.center_pos, sprite_b.radius))
		return (true);
	return (false);
	// return (CheckCollisionCircles(sprite_a.center_pos, sprite_a.radius,
	//    sprite_b.center_pos, sprite_b.radius));
}

void check_colliding_asteroids()
{
	int	i;
	int	j;

	i = 0;
	while (i < MAX_ASTEROIDS - 1)
	{
		j = i + 1;
		while (j < MAX_ASTEROIDS)
		{
			if (check_collision(game.asteroid[i], game.asteroid[j]))
			{
				game.asteroid[i] = initialize_asteroid(game.asteroid[i]);
				game.asteroid[j] = initialize_asteroid(game.asteroid[j]);
			}
			j++;
		}
		i++;
	}
}

void initialize_out_of_bounds_asteroids()
{
	float extra_padding = 150;
	float width = (float)GetScreenWidth() + extra_padding;
	float height = (float)GetScreenHeight() + extra_padding;
	Rectangle screen_collider = { 0 - extra_padding/2, 0 - extra_padding / 2, width, height };
	int i = 0;
	//DrawRectangle(screen_collider.x, screen_collider.y, screen_collider.width, screen_collider.height, BLACK);
	
	while (i < MAX_ASTEROIDS)
	{
		if(!CheckCollisionCircleRec(game.asteroid[i].center_pos, game.asteroid[i].radius, screen_collider))
			game.asteroid[i] = initialize_asteroid(game.asteroid[i]);
		i++;
	}
	printf("Out of bounds\n");
}
