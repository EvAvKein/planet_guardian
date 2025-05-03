#ifndef PLANET_GUARDIAN_H
# define PLANET_GUARDIAN_H

# include <stdlib.h>
# include "raylib.h"
# include "raymath.h"
# include <time.h>

typedef struct sprite
{
    Vector2     pos;
    Texture2D   texture;
    float       radius;
    Vector2     direction;
    Vector2     center_pos;
    bool        is_inside_screen;
	float       speed;
} sprite_t;

typedef struct shadow {
    Texture2D   texture;
    int         rotation;
    int         speed;
} shadow_t;

typedef struct cold {
    Texture2D   texture;
    unsigned char value;
    float elapsed;
    float interval;
    // float withdrawal_limit;
    // float withdrawal_current;
} cold_t;

typedef struct game
{
    sprite_t   planet;
    sprite_t   asteroid[5];
    cold_t     cold;
    shadow_t   shadow;
} game_t;

extern game_t game;

void	update_planet_condition(float delta_time);

#endif
