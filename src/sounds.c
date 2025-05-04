#include "planet_guardian.h"

void soundLoader()
{
    game.sound.shield = LoadSound("assets/audio/final/shield_collision.wav");
    game.sound.theme = LoadMusicStream("assets/audio/final/theme.mp3");
	game.sound.earth = LoadSound("assets/audio/final/asteroid_collision.mp3");
	game.sound.asteroid = LoadSound("assets/audio/final/asteroid_collision.mp3");
	SetMusicVolume(game.sound.theme, 0.4);
	SetSoundVolume(game.sound.earth, 1);
	SetSoundVolume(game.sound.asteroid, 0.8);
	SetSoundVolume(game.sound.shield, 1);
}
void play_shield_sound()
{
    PlaySound(game.sound.shield);
}

void playTheme()
{
    PlayMusicStream(game.sound.theme);
}

void stopTheme()
{
    StopMusicStream(game.sound.theme);
}

void play_asteroid_collision()
{
	PlaySound(game.sound.asteroid);
}

void play_earth_collision()
{
	PlaySound(game.sound.earth);
}
