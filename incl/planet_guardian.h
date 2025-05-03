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
    int       speed;
} sprite_t;

typedef struct game
{
    sprite_t   planet;
    sprite_t   asteroid[5];
} game_t;

extern game_t game;

Vector2 moveTowardsWithGravity(Vector2 current, Vector2 direction, int speed, Vector2 planetCenter);
Vector2 generateAsteroidPos();
Vector2 generateRandomDir(Vector2 current);

#endif
