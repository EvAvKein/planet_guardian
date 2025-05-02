#ifndef PLANET_GUARDIAN_H
# define PLANET_GUARDIAN_H

# include <stdlib.h>
# include "raylib.h"
# include "raymath.h"
# include <time.h>

typedef struct sprite
{
    Vector2 pos = {0, 0};
    Texture2D texture;
} sprite_t

typedef struct game
{
    Texture2D planet;
    Texture2D asteroid[5];
} game_t;

extern game_t game;

#endif