#include "planet_guardian.h"

void soundLoader()
{
    game.sound.shield = LoadSound("assets/audio/final/shield_collision.mp3");
    game.sound.theme = LoadSound("assets/audio/final/theme.mp3");
	game.sound.asteroid = LoadSound("assets/audio/final/asteroid_collision.mp3");
	game.sound.earth = LoadSound("assets/audio/final/earth_collision.mp3");
}

void play_shield_sound()
{
    PlaySound(game.sound.shield);
}

void playTheme()
{
    PlaySound(game.sound.theme);
}

void play_asteroid_collision()
{
	PlaySound(game.sound.asteroid);
}

void play_earth_collision()
{
	PlaySound(game.sound.earth);
}
