#include "planet_guardian.h"

void play_shield_sound()
{
    Sound shield = LoadSound("assets/audio/shield_hit.mp3");
    PlaySound(shield);
}