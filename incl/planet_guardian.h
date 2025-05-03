#ifndef PLANET_GUARDIAN_H
# define PLANET_GUARDIAN_H

# include <stdlib.h>
# include "raylib.h"
# include "raymath.h"
# include <time.h>

void draw_shield(float angle);

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

typedef struct game
{
    sprite_t   planet;
    sprite_t   asteroid[5];
    sprite_t   shield;
} game_t;



extern game_t game;


#endif
