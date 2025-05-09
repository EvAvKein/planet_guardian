#include "planet_guardian.h"

void update_planet_condition(float delta_time, float shieldAngle)
{
	// Update temperature timer
	game.temp.elapsed += delta_time;
	if (game.temp.elapsed > game.temp.interval)
	{
		game.temp.elapsed -= game.temp.interval;

		// Convert shield angle from radians to degrees
		float shieldDeg = fmodf(shieldAngle * (180.0f / 3.141592653), 360.0f);
		if (shieldDeg < 0.0f) shieldDeg += 360.0f;

		// Normalize shadow angle
		float shadowDeg = fmodf((float)game.shadow.rotation, 360.0f);
		if (shadowDeg < 0.0f) shadowDeg += 360.0f;

		// Compute shortest angular difference (0 to 180 degrees)
		float diff = fabsf(shadowDeg - shieldDeg);
		if (diff > 180.0f) diff = 360.0f - diff;

		// Adjust temperature level based on shield alignment
		if (diff > 90.0f)
		{
			if (game.temp.value + TEMP_CHANGE >= MAX_TEMP)
				game.temp.value = MAX_TEMP;
			if (game.temp.value < MAX_TEMP)
				game.temp.value += TEMP_CHANGE;
		}
		else
		{
			if (game.temp.value - TEMP_CHANGE <= MIN_TEMP)
				game.temp.value = MIN_TEMP;
			if (game.temp.value > MIN_TEMP)
				game.temp.value -= TEMP_CHANGE;
		}
	}

	// Update shadow rotation timer
	game.shadow.elapsed += delta_time;
	if (game.shadow.elapsed > game.shadow.interval)
	{
		game.shadow.elapsed -= game.shadow.interval;
		game.shadow.rotation = (game.shadow.rotation + 1) % 360;
	}
}
