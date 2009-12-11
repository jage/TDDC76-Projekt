/*
 *	Audio.h
 *
 *	Creator: Johan Wågberg
 *	Date: 091205
 *
 *	Plays sounds and music.
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include "SDLInclude.h"

#define NROFMUSICTRACKS 1
#define NROFSOUNDS 3

class Audio
{
public:

	Audio();
	virtual ~Audio();

	void init();
	void uninit();
	void playMusic(const int& musicIndex, const int& loop) const;
	void playSound(const int& soundIndex) const;
	void stopMusic() const;
	void stopSound() const;
	void stopAllAudio() const;
	void setMusicVolume(const int& volume);
	const int getMusicVolume() const;
	void setSoundVolume(const int& volume);
	const int getSoundVolume() const;

private:
	bool SDL_Audio_Enabled_;
	int currentlySelectedMusic_;
	int musicVolume_;
	int soundVolume_;
	Mix_Chunk* sound_[NROFSOUNDS];
	Mix_Music* musicTrack_[NROFMUSICTRACKS];

	void loadMusicIntoMemory();
	void unloadMusicFromMemory();
	void loadSoundsIntoMemory();
	void unloadSoundsFromMemory();
};

#endif


