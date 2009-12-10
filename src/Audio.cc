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


void Audio::uninit()
{
	stopAllAudio();
	Mix_AllocateChannels(0);
	unloadSoundsFromMemory();
	unloadMusicFromMemory();
	Mix_CloseAudio();
	SDL_Audio_Enabled_ = false;
}

void Audio::stopSound() const
{
	Mix_HaltChannel(-1);
}

void Audio::stopAllAudio() const
{
	stopSound();
	stopMusic();
}


void Audio::loadMusicIntoMemory()
{
	musicTrack_[0] = Mix_LoadMUS("Opening_Music.ogg");
	if(!musicTrack_[0])
	{
		cerr << Mix_GetError() << endl;
	}
	Mix_VolumeMusic(musicVolume_);
}

void Audio::unloadMusicFromMemory()
{
	stopMusic();

	for (int musicIndex = 0; musicIndex < NROFMUSICTRACKS; musicIndex++)
	{
		Mix_FreeMusic(musicTrack_[musicIndex]);
		musicTrack_[musicIndex] = NULL;
	}
}

void Audio::playMusic(const int &musicIndex, const int &loop) const
{
	if (SDL_Audio_Enabled_ == false) return;
	if (Mix_PlayingMusic() == 1) Mix_HaltMusic();
	if (musicVolume_ == 0) return;

	if (Mix_PlayMusic(musicTrack_[musicIndex], loop) == -1)
	{
		cerr << Mix_GetError() << endl;
	}

	Mix_VolumeMusic(musicVolume_);
}

void Audio::loadSoundsIntoMemory()
{
	sound_[0] = Mix_LoadWAV("sounds/Danger.wav");
	if (!sound_[0])
	{
		cerr << Mix_GetError() << endl;
	}
	Mix_VolumeChunk(sound_[0], 128);

	sound_[1] = Mix_LoadWAV("sounds/Game_Over.wav");
	if (!sound_[1])
	{
		cerr << Mix_GetError() << endl;
	}
	Mix_VolumeChunk(sound_[1], 128);

	sound_[2] = Mix_LoadWAV("sounds/High_Score.wav");
	if (!sound_[2])
	{
		cerr << Mix_GetError() << endl;
	}
	Mix_VolumeChunk(sound_[2], 128);

	sound_[3] = Mix_LoadWAV("sounds/Incoming_Line.wav");
	if (!sound_[3])
	{
		cerr << Mix_GetError() << endl;
	}
	Mix_VolumeChunk(sound_[3], 128);

	sound_[4] = Mix_LoadWAV("sounds/Level_Up.wav");
	if (!sound_[4])
	{
		cerr << Mix_GetError() << endl;
	}
	Mix_VolumeChunk(sound_[4], 128);

	sound_[5] = Mix_LoadWAV("sounds/Line_Cleared.wav");
	if (!sound_[5])
	{
		cerr << Mix_GetError() << endl;
	}
	Mix_VolumeChunk(sound_[5], 128);

	sound_[6] = Mix_LoadWAV("sounds/Move_Piece.wav");
	if (!sound_[6])
	{
		cerr << Mix_GetError() << endl;
	}
	Mix_VolumeChunk(sound_[6], 128);
	
	sound_[7] = Mix_LoadWAV("sounds/New_Top_High_Score.wav");
	if (!sound_[7])
	{
		cerr << Mix_GetError() << endl;
	}
	Mix_VolumeChunk(sound_[7], 128);

	sound_[8] = Mix_LoadWAV("sounds/Piece_Collision.wav");
	if (!sound_[8])
	{
		cerr << Mix_GetError() << endl;
	}
	Mix_VolumeChunk(sound_[8], 128);

	sound_[9] = Mix_LoadWAV("sounds/Piece_Drop.wav");
	if (!sound_[9])
	{
		cerr << Mix_GetError() << endl;
	}
	Mix_VolumeChunk(sound_[9], 128);

	sound_[10] = Mix_LoadWAV("sounds/Piece_Rotate.wav");
	if (!sound_[10])
	{
		cerr << Mix_GetError() << endl;
	}
	Mix_VolumeChunk(sound_[10], 128);

	sound_[11] = Mix_LoadWAV("sounds/Tetris_Cleared.wav");
	if (!sound_[11])
	{
		cerr << Mix_GetError() << endl;
	}
	Mix_VolumeChunk(sound_[11], 128);
}

void Audio::unloadSoundsFromMemory()
{
	stopSound();

	for (int soundIndex = 0; soundIndex < NROFSOUNDS; soundIndex++)
	{
		Mix_FreeChunk(sound_[soundIndex]);
		sound_[soundIndex] = NULL;
	}
}

void Audio::playSound(const int& soundIndex) const
{
	if (SDL_Audio_Enabled_ == false)  return;
	
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

void Audio::setMusicVolume(const int& volume)
{
	musicVolume_ = volume;
}

const int Audio::getMusicVolume() const
{
	return musicVolume_;
}

void Audio::setSoundVolume(const int &volume)
{
	soundVolume_ = volume;
}

const int Audio::getSoundVolume() const
{
	return soundVolume_;
}

void Audio::stopMusic() const
{
	Mix_HaltMusic();
}
