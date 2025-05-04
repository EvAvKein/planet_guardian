#include "planet_guardian.h"

void soundLoader()
{
    game.sound.shield = LoadSound("assets/audio/shield_hit.mp3");
    game.sound.theme = LoadSound("assets/audio/theme.mp3");
}
void play_shield_sound()
{
    PlaySound(game.sound.shield);
}

void playTheme()
{
    PlaySound(game.sound.theme);
}
