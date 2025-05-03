#include "planet_guardian.h"

bool check_collision(sprite_t sprite_a, sprite_t sprite_b)
{
	if (CheckCollisionCircles(sprite_a.center_pos, sprite_a.radius, sprite_b.center_pos, sprite_b.radius))
		return (true);
	return (false);
	// return (CheckCollisionCircles(sprite_a.center_pos, sprite_a.radius,
	//    sprite_b.center_pos, sprite_b.radius));
}
