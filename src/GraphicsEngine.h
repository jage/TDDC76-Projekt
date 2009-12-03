/*
 *	GraphicsEngine.h
 *
 *	Creator: Johan Wågberg
 *	Date: 091123
 *
 *	Ritar ut Element och text på skärmen.
 */


#ifndef GRAPHICSENGINE_H_
#define GRAPHICSENGINE_H_

#include "SDLInclude.h"
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
	void clearScreenBuffer(const unsigned int color);
	void clearScreenBuffer();
	void showScreenBufferOnScreen();
	void drawTextToScreenBuffer(const std::string& text, int xScreenPos, int yScreenPos, int red, int blue, int green, int fontIndex = 0);
	void drawOutlinedTextToScreenBuffer(const std::string& text, int xScreenPos, int yScreenPos, int red, int blue, int green, int fontIndex = 0);
	void drawSDLSurfaceToScreenBuffer(SDL_Surface* image, int xScreenPos, int yScreenPos);

private:
	SDL_Surface* screen;
	SDL_Surface* source_image;
	SDL_Surface* cannon[DEGREES];
	TTF_Font* font[NROFFONTS];
	int width_;
	int height_;

	void init();
	void uninit();
	void loadFontsIntoMemory();
	void unloadFontsFromMemory();
	void loadCannonSpritesIntoMemory();
	void unloadCannonSpritesFromMemory();
	SDL_Surface* loadImageFromDisc(const std::string&);
	SDL_Rect getClippingRectangle(const PANZER_IMAGE&) const;
};

#endif
