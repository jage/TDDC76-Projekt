#ifndef AUDIO_H_
#define AUDIO_H_
#include "SDL/SDL_mixer.h"
#include "SDL/SDL.h"


#define NROFMUSICTRACKS 1
#define NROFSOUNDS 12

class Audio
{
public:

	Audio();
	virtual ~Audio();

	void init();
	void uninit();
	void playMusic(const int& musicIndex, const int& loop);
	void playSound(const int& soundIndex);
	void stopMusic();
	void stopAllSound();
	void setMusicVolume(const int& volume);
	const int getMusicVolume();
	void setSoundVolume(const int& volume);
	const int getSoundVolume();

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

