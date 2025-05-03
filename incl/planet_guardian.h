#ifndef PLANET_GUARDIAN_H
# define PLANET_GUARDIAN_H

# include <stdlib.h>
# include "raylib.h"
# include "raymath.h"
# include <time.h>

# define MAX_ASTEROIDS 5
# define MAX_ASTEROID_SPEED 10.0f
# define MIN_ASTEROID_RADIUS 10.0f
# define MAX_ASTEROID_RADIUS 20.0f
# define GRAVITYPULL_SCALE 0.00001f

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
    sprite_t   asteroid[MAX_ASTEROIDS];
} game_t;

extern game_t game;

Vector2 moveTowardsWithGravity(Vector2 current, Vector2 direction, int speed, Vector2 planetCenter);
Vector2 generateAsteroidPos();
Vector2 generateRandomDir(Vector2 current);
void initialize_all_asteroids();
sprite_t initialize_asteroid(sprite_t asteroid);
Vector2 get_center_pos(sprite_t sprite);

#endif
