#ifndef PLANET_GUARDIAN_H
# define PLANET_GUARDIAN_H

# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include "raylib.h"
# include "raymath.h"

# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 1000

# define MAX_HEALTH 5

# define MAX_ASTEROIDS 15
# define MAX_ASTEROID_SPEED 10.0f
# define MIN_ASTEROID_RADIUS 10.0f
# define MAX_ASTEROID_RADIUS 20.0f
# define GRAVITYPULL_SCALE 0.000006f
# define DIRECTION_CIRCLE_SIZE_TIMES_PLANET 6
# define SHIELD_RED_TIME 0.5f

# define TEMP_CHANGE 10
# define MAX_TEMP 255
# define MIN_TEMP -255

typedef enum gamestate
{
    START,
    GAME,
    END
} state_t;

typedef enum losestate
{
    METEORS,
    HEAT,
    COLD
} losestate_t;

typedef struct sprite
{
    Vector2     pos;
    Texture2D   texture;
    float       radius;
    Vector2     direction;
    Vector2     center_pos;
    bool        is_inside_screen;
	float       speed;
    float       rotation;
} sprite_t;

typedef struct shield {
    sprite_t    sprite;
    Texture2D   red_shield_texture;
    Texture2D   shield_texture;
    float       angle;
    int         direction;
	float		spin_speed;
    bool        shieldWasHit;
    double      lastShieldHitTime;
} shield_t;

typedef struct shadow {
    Texture2D   texture;
    int         rotation;
    float       elapsed;
    float       interval;
} shadow_t;

typedef struct temp {
    Texture2D   hot_texture;
    Texture2D   cold_texture;
    int         value;
    float       elapsed;
    float       interval;
} temp_t;

typedef struct sound
{
    Sound       shield;
    Sound       theme;
	Sound		asteroid;
	Sound		earth;
} sound_t;


typedef struct game
{
    unsigned int health;
    sound_t    sound;
    sprite_t   planet;
    shield_t   shield;
    sprite_t   asteroid[MAX_ASTEROIDS];
    temp_t     temp;
    shadow_t   shadow;
    Texture2D  background;
    Font        font;
    Texture2D   logo;
    Texture2D   menu;
    char   *asteroid_textures[4];
    int max_health;
    int current_health;
    state_t state;
    losestate_t lose_reason;
    // Texture2D   lose_textures[3];
    float       time_since_death;
    float	time_since_live;
} game_t;

extern game_t game;

void gameplay_frame();

void textureLoader();
void textureUnload();

void playTheme();
void drawMenu();
void deathScreen();
void soundLoader();
void printp(char *msg, float x, float y, float size, Color color);
Vector2 moveTowardsWithGravity(Vector2 current, Vector2 direction, int speed, Vector2 planetCenter);
Vector2 generateAsteroidPos();
Vector2 generateRandomDir(Vector2 current);
char *random_asteroid_texture();
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
void play_earth_collision();
void play_asteroid_collision();
void draw_red_shield(float delta_time);
void draw_repeat_background(int	screen_width, int screen_height);

char *ft_strjoin(char const *s1, char const *s2);

#endif
