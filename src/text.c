#include "planet_guardian.h"

void printp(char *msg, float x, float y, float size, Color color)
{
    DrawTextEx(game.font, msg, (Vector2){x, y}, size * (float)game.font.baseSize, 1.0f, color);
}
