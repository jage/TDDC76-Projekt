#ifndef AUDIO_
#define AUDIO_
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
	void setMusicVolume(const int& volume);
	void setSoundVolume(const int& volume);
	const int getMusicVolume();
	const int getSoundVolume();
	void stopMusic();
	void stopAllSound();

private:
	void loadMusicIntoMemory();
	void unloadMusicFromMemory();
	void loadSoundsIntoMemory();
	void unloadSoundsFromMemory();
	bool SDL_Audio_Enabled_;
	int currentlySelectedMusic_;
	int musicVolume_;
	int soundVolume_;
	Mix_Chunk* sound_[NROFSOUNDS];
	Mix_Music* musicTrack_[NROFMUSICTRACKS];
};
#endif
