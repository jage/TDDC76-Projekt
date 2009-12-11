#include "Audio.h"
#include <iostream>
#include "SDLInclude.h"

using namespace std;

Audio::Audio()
: SDL_Audio_Enabled_(false), currentlySelectedMusic_(0), musicVolume_(64), soundVolume_(64)
{
	init();
}

Audio::~Audio()
{}

/*
 * Initiates SDL_AUDIO if needed and the audio mixer. Allocates channels
 * and loads all music and sound effects into memory
 */
void Audio::init()
{
	if (SDL_WasInit(SDL_INIT_AUDIO) == 0)
	{
		if (SDL_Init(SDL_INIT_AUDIO) == -1)
		{
			cerr << "Unable to init SDL" << endl;
			return;
		}
	}
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 512) == 0) {
		SDL_Audio_Enabled_ = true;
	}
	else {
		cerr << "Unable to start Mixer" << endl;
		return;
	}
	Mix_AllocateChannels(16);
	loadMusicIntoMemory();
	loadSoundsIntoMemory();
}

/*
 * Frees all allocated memory and closes the audio mixer.
 */
void Audio::uninit()
{
	if (SDL_Audio_Enabled_) {
		stopAllAudio();
		Mix_AllocateChannels(0);
		unloadSoundsFromMemory();
		unloadMusicFromMemory();
		Mix_CloseAudio();
		SDL_Audio_Enabled_ = false;
	}
}

/*
 * Stops all sound effects currently playing.
 */
void Audio::stopSound() const
{
	Mix_HaltChannel(-1);
}

/*
 * Stops the music currently playing.
 */
void Audio::stopAllAudio() const
{
	stopSound();
	stopMusic();
}

/*
 * Loads all music into memory
 */
void Audio::loadMusicIntoMemory()
{
	musicTrack_[0] = Mix_LoadMUS("Opening_Music.ogg");
	if(!musicTrack_[0])
	{
		cerr << Mix_GetError() << endl;
	}
	Mix_VolumeMusic(musicVolume_);
}

/*
 * Frees the memory of all music.
 */
void Audio::unloadMusicFromMemory()
{
	stopMusic();

	for (int musicIndex = 0; musicIndex < NROFMUSICTRACKS; musicIndex++)
	{
		if (musicTrack_[musicIndex] != NULL) {
			Mix_FreeMusic(musicTrack_[musicIndex]);
			musicTrack_[musicIndex] = NULL;
		}
	}
}

/*
 * Plays selected music track.
 */
void Audio::playMusic(const int &musicIndex, const int &loop) const
{
	if (SDL_Audio_Enabled_ == false) return;
	if (Mix_PlayingMusic() == 1) Mix_HaltMusic();
	if (musicVolume_ == 0) return;
	if (musicIndex < 0 || musicIndex >= NROFMUSICTRACKS) return;

	if (Mix_PlayMusic(musicTrack_[musicIndex], loop) == -1)
	{
		cerr << Mix_GetError() << endl;
		return;
	}

	Mix_VolumeMusic(musicVolume_);
}

/*
 * Loads all sound effects into memory
 */
void Audio::loadSoundsIntoMemory()
{
	sound_[0] = Mix_LoadWAV("sounds/fire.wav");
	if (!sound_[0])
	{
		cerr << Mix_GetError() << endl;
		return;
	}
	Mix_VolumeChunk(sound_[0], 128);

	sound_[1] = Mix_LoadWAV("sounds/explosion.wav");
	if (!sound_[1])
	{
		cerr << Mix_GetError() << endl;
		return;
	}
	Mix_VolumeChunk(sound_[1], 128);

	sound_[2] = Mix_LoadWAV("sounds/wind.wav");
	if (!sound_[2])
	{
		cerr << Mix_GetError() << endl;
		return;
	}
	Mix_VolumeChunk(sound_[2], 128);
}

/*
 * Unloads all sound effects from mamory.
 */
void Audio::unloadSoundsFromMemory()
{
	stopSound();

	for (int soundIndex = 0; soundIndex < NROFSOUNDS; soundIndex++)
	{
		if (sound_[soundIndex] != NULL) {
			Mix_FreeChunk(sound_[soundIndex]);
			sound_[soundIndex] = NULL;
		}
	}
}

/*
 * Plays selected sound effect.
 */
void Audio::playSound(const int& soundIndex) const
{
	if (SDL_Audio_Enabled_ == false)  return;
	if (soundIndex < 0 || soundIndex >= NROFSOUNDS) return;
	
	Mix_Volume( 0, soundVolume_);
	Mix_Volume( 1, soundVolume_);
	Mix_Volume( 2, soundVolume_);
	Mix_Volume( 3, soundVolume_);
	Mix_Volume( 4, soundVolume_);
	Mix_Volume( 5, soundVolume_);
	Mix_Volume( 6, soundVolume_);
	Mix_Volume( 7, soundVolume_);
	Mix_Volume( 8, soundVolume_);
	Mix_Volume( 9, soundVolume_);
	Mix_Volume(10, soundVolume_);
	Mix_Volume(11, soundVolume_);
	Mix_Volume(12, soundVolume_);
	Mix_Volume(13, soundVolume_);
	Mix_Volume(14, soundVolume_);
	Mix_Volume(15, soundVolume_);

	if(Mix_PlayChannel(-1, sound_[soundIndex], 0) == -1)
	{
		cerr << Mix_GetError() << endl;
	}
}

/*
 * Sets the music volume.
 */
void Audio::setMusicVolume(const int& volume)
{
	musicVolume_ = volume;
}

/*
 * Returns the music volume.
 */
const int Audio::getMusicVolume() const
{
	return musicVolume_;
}

/*
 * Sets the sound effects colume.
 */
void Audio::setSoundVolume(const int &volume)
{
	soundVolume_ = volume;
}

/* 
 * Returns the sound effects volume.
 */
const int Audio::getSoundVolume() const
{
	return soundVolume_;
}

/*
 * Stops the music.
 */
void Audio::stopMusic() const
{
	Mix_HaltMusic();
}
