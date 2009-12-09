#include "SDL_mixer.h"
#include "SDL.h"

#define NROFMUSICTRACKS 1
#define NROFSOUNDS 12

class Audio
{
public:

	Audio();
	virtual ~Audio();

	void init();
	void uninit();
	void loadMusicIntoMemory();
	void unloadMusicFromMemory();
	void playMusic(const int& musicIndex, const int& loop);
	void loadSoundsIntoMemory();
	void unloadSoundsFromMemory();
	void playSound(const int& soundIndex);
	void setMusicVolume(const int& volume);
	void stopMusic();
	void stopAllSound();
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
};
