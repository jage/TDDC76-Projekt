/*
 *	GraphicsEngine.h
 *
 *	Creator: Johan Wgberg
 *	Date: 091123
 *
 *	Ritar ut Element p� sk�rmen.
 */


#ifndef GRAPHICSENGINE_H_
#define GRAPHICSENGINE_H_

#include "SDLInclude.h"
#include "SDL_ttf.h"
#include "Element.h"
#include "Enums.h"
#include <vector>
#include <string>

const int DEGREES = 360;
const int NROFFONTS = 1;

class GraphicsEngine
{
public:
	GraphicsEngine(const int& = 640, const int& = 480);
	~GraphicsEngine();

	void drawToScreenBuffer(const std::vector<Element>&);
	void drawToScreenBuffer(const Element&);
	void clearScreenBuffer(const unsigned int);
	void clearScreenBuffer();
	void showScreenBufferOnScreen();
	void drawTextToScreenBuffer(const std::string&, int, int);
	void drawTextWithShadowToScreenBuffer(const std::string&, int, int);

private:
	SDL_Surface* screen;
	SDL_Surface* source_image;
	SDL_Surface* cannon[DEGREES];
	TTF_Font* font[NROFFONTS];


	void init();
	void uninit();
	void loadFontsIntoMemory();
	void unloadFontsFromMemory();
	void loadCannonSpritesIntoMemory();
	void unloadCannonSpritesFromMemory();
	SDL_Surface* loadImageFromDisc(const std::string&);
	SDL_Rect get_clipping_rect(const PANZER_IMAGE&) const;
};

#endif
