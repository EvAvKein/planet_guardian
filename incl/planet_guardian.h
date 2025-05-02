#ifndef PLANET_GUARDIAN_H
# define PLANET_GUARDIAN_H

# include <stdlib.h>
# include "raylib.h"

typedef struct game
{
    Texture2D planet;
    Texture2D asteroid;
} game_t;

extern game_t game;

#endif