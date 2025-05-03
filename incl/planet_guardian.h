#ifndef PLANET_GUARDIAN_H
# define PLANET_GUARDIAN_H

# include <stdlib.h>
# include "raylib.h"
# include "raymath.h"
# include <time.h>
# include <stdio.h>

# define MAX_ASTEROIDS 100
# define MAX_ASTEROID_SPEED 10.0f
# define MIN_ASTEROID_RADIUS 10.0f
# define MAX_ASTEROID_RADIUS 20.0f
# define GRAVITYPULL_SCALE 0.00001f

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

typedef struct shadow {
    Texture2D   texture;
    int         rotation;
    float elapsed;
    float interval;
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
    Font       pixelTtf;
    sprite_t   shield;
    sprite_t   asteroid[MAX_ASTEROIDS];
    cold_t     cold;
    shadow_t   shadow;
    Texture2D  background;
} game_t;

extern game_t game;

void printp(char *msg, int x, int y, float size, Color color);
Vector2 moveTowardsWithGravity(Vector2 current, Vector2 direction, int speed, Vector2 planetCenter);
Vector2 generateAsteroidPos();
Vector2 generateRandomDir(Vector2 current);
void initialize_all_asteroids();
sprite_t initialize_asteroid(sprite_t asteroid);
Vector2 get_center_pos(sprite_t sprite);
bool check_collision(sprite_t sprite_a, sprite_t sprite_b);
void draw_asteroids();
void	update_planet_condition(float delta_time);

#endif
