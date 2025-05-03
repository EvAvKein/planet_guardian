#include "planet_guardian.h"


void update_planet_condition(float delta_time, float shieldAngle)
{
	// Update cold timer
	game.cold.elapsed += delta_time;
	if (game.cold.elapsed > game.cold.interval)
	{
		game.cold.elapsed -= game.cold.interval;

		// Convert shield angle from radians to degrees
		float shieldDeg = fmodf(shieldAngle * (180.0f / 3.141592653), 360.0f);
		if (shieldDeg < 0.0f) shieldDeg += 360.0f;

		// Normalize shadow angle
		float shadowDeg = fmodf((float)game.shadow.rotation, 360.0f);
		if (shadowDeg < 0.0f) shadowDeg += 360.0f;

		// Compute shortest angular difference (0 to 180 degrees)
		float diff = fabsf(shadowDeg - shieldDeg);
		if (diff > 180.0f) diff = 360.0f - diff;

		// Adjust cold level based on shield alignment
		if (diff < 90.0f)
		{
			if (game.cold.value < MAX_TEMP - TEMP_CHANGE)
				game.cold.value += TEMP_CHANGE;
		}
		else
		{
			
			if (game.cold.value > MIN_TEMP + TEMP_CHANGE)
				game.cold.value -= TEMP_CHANGE;
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


