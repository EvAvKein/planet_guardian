#ifndef PLANET_GUARDIAN_H
# define PLANET_GUARDIAN_H

# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include "raylib.h"
# include "raymath.h"

# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 1000

# define MAX_ASTEROIDS 10
# define MAX_ASTEROID_SPEED 5.0f
# define MIN_ASTEROID_RADIUS 10.0f
# define MAX_ASTEROID_RADIUS 20.0f
# define GRAVITYPULL_SCALE 0.000005f

# define TEMP_CHANGE 10 
# define MAX_TEMP 255
# define MIN_TEMP 0

typedef enum gamestate 
{
    START,
    GAME,
    END
} state_t;

typedef enum gamestate 
{
    START,
    GAME,
    END
} state_t;

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

typedef struct shield {
    sprite_t    sprite;
    float       angle;
    int         direction;
} shield_t;

typedef struct shadow {
    Texture2D   texture;
    int         rotation;
    float       elapsed;
    float       interval;
} shadow_t;

typedef struct cold {
    Texture2D       texture;
    unsigned char   value;
    float           elapsed;
    float           interval;
    // float withdrawal_limit;
    // float withdrawal_current;
} cold_t;

typedef struct game
{
    sprite_t   planet;
    shield_t   shield;
    sprite_t   asteroid[MAX_ASTEROIDS];
    cold_t     cold;
    shadow_t   shadow;
    Texture2D  background;
    Font        font;
    state_t    state;
    Texture2D   logo;
    Texture2D   menu;
} game_t;

extern game_t game;

void gameplay_frame();

void textureLoader();
void textureUnload();


void printp(char *msg, float x, float y, float size, Color color);
Vector2 moveTowardsWithGravity(Vector2 current, Vector2 direction, int speed, Vector2 planetCenter);
Vector2 generateAsteroidPos();
Vector2 generateRandomDir(Vector2 current);
void initialize_all_asteroids();
sprite_t initialize_asteroid(sprite_t asteroid);
Vector2 get_center_pos(sprite_t sprite);
bool check_collision(sprite_t sprite_a, sprite_t sprite_b);
void draw_asteroids();
void draw_shield(float angle);
void check_colliding_asteroids();
void initialize_out_of_bounds_asteroids();
void update_planet_condition(float delta_time, float shieldAngle);
void play_shield_sound();

#endif
