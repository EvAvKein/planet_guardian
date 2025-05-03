#include "planet_guardian.h"

void	update_planet_condition(float delta_time)
{
	game.cold.elapsed += delta_time;
	if (game.cold.elapsed > game.cold.interval)
	{
		game.cold.elapsed -= game.cold.interval;
		game.cold.value += 1;
	}

	game.shadow.elapsed += delta_time;
	if (game.shadow.elapsed > game.shadow.interval)
	{
		game.shadow.elapsed -= game.shadow.interval;
		game.shadow.rotation = (game.shadow.rotation + 1) % 360;
	}
}
