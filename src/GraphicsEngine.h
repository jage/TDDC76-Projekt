/*
 *	GraphicsEngine.h
 *
 *	Creator: Johan W�gberg
 *	Date: 091123
 *
 *	Ritar ut Element och text p� sk�rmen.
 */


#ifndef GRAPHICSENGINE_H_
#define GRAPHICSENGINE_H_

#include "SDLInclude.h"
#include "Element.h"
#include "MovableElement.h"
#include "Enums.h"
#include <vector>
#include <string>

const int DEGREES = 360;
const int NROFFONTS = 2;
const int NROFBUTTONIMG = 5;

class GraphicsEngine
{
public:
	GraphicsEngine(const int& = 640, const int& = 480);
	~GraphicsEngine();

	void drawToScreenBuffer(const std::vector<Element>&);
	void drawToScreenBuffer(const std::vector<Element*>&);
	void drawToScreenBuffer(const std::vector<MovableElement*>&);
	void drawToScreenBuffer(const Element&);
	void clearScreenBuffer(const unsigned int& color);
	void clearScreenBuffer();
	void showScreenBufferOnScreen();
	void drawTextToScreenBuffer(const std::string& text, const int& xScreenPos, const int& yScreenPos, const int& red, const int& blue, const int& green, const PANZER_FONT& font = LAZY32);
	void drawOutlinedTextToScreenBuffer(const std::string& text, const int& xScreenPos, const int& yScreenPos, const int& red, const int& blue, const int& green, const PANZER_FONT& fontName = LAZY32);
	void drawSDLSurfaceToScreenBuffer(SDL_Surface* image, const int& xScreenPos, const int& yScreenPos);
	void drawButton(const std::string& text, const int& xScreenPos, const int& yScreenPos, const bool& active, const PANZER_FONT& textfont, const PANZER_ALIGNMENT& align);
	void drawRectangle(const int& xScreenPos, const int& yScreenPos, const int& width, const int& height, const int& red, const int& green, const int& blue);
	void drawFixedWidthButton(	const std::string& text,
								const int& xScreenPos,
								const int& yScreenPos,
								const int& width,
								const bool& active,
								const PANZER_FONT& textfont,
								const int& red = 255,
								const int& green = 255,
								const int& blue = 255);

private:
	SDL_Surface* screen;
	SDL_Surface* source_image;
	SDL_Surface* cannonball;
	SDL_Surface* cannon[2*DEGREES];
	SDL_Surface* buttons[NROFBUTTONIMG];
	TTF_Font* font[NROFFONTS];
	int width_;
	int height_;

	void init();
	void uninit();
	void loadFontsIntoMemory();
	void unloadFontsFromMemory();
	void loadCannonSpritesIntoMemory();
	void unloadCannonSpritesFromMemory();
	void loadButtonSpritesIntoMemory();
	void unloadButtonSpritesFromMemory();
	int getFontNr(const PANZER_FONT& font);
	void drawEmptyButton(int xScreenPos, int yScreenPos, const int& nrOfMiddles, const bool& active);
	SDL_Surface* generateTextSurface(const std::string& text, const PANZER_FONT& font, const SDL_Color& color);
	SDL_Surface* loadImageFromDisc(const std::string&, const bool& transparent = false);
	SDL_Rect getClippingRectangle(const PANZER_IMAGE&) const;
	SDL_Surface* flipImageHorizontally(SDL_Surface*);
};

#endif
