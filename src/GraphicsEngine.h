/*
 *	GraphicsEngine.h
 *
 *	Creator: Johan Wågberg
 *	Date: 091123
 *
 *	Draws Elements, buttons and text to screen.
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
const int NROFFONTS = 3;
const int NROFBUTTONIMG = 5;
const int NROFBACKGROUNDS = 4;

class GraphicsEngine
{
public:
	GraphicsEngine(const int& = 640, const int& = 480);
	~GraphicsEngine();

	void drawToScreenBuffer(const std::vector<Element*>&);
	void drawToScreenBuffer(const std::vector<MovableElement*>&);
	void drawToScreenBuffer(const Element&);
	void clearScreenBuffer(const unsigned int& color = (0xff << 16 | 0xff << 8 | 0xff << 0));
	void showScreenBufferOnScreen();
	void drawBackgroundToScreenBuffer(const int& backgroundNr = 0);
	void drawPowerBarToScreenBuffer(const int& xScreenPos, const int& yScreenPos, const int& width, const int& height, const int& percentage);
	void drawWindBarToScreenBuffer(const int& xScreenPos, const int& yScreenPos, const int& width, const int& height, const int& percentage);
	void drawTextToScreenBuffer(const std::string& text, const int& xScreenPos, const int& yScreenPos, const int& red, const int& blue, const int& green, const PANZER_FONT& font = LAZY32);
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
	SDL_Surface* screen;						//screen buffer
	SDL_Surface* cannonball;					//picture of cannonbal
	SDL_Surface* backgrounds[NROFBACKGROUNDS];	//all the backgrounds
	SDL_Surface* cannon[2*DEGREES];				//prerotated pictures of cannon both left and right
	SDL_Surface* buttons[NROFBUTTONIMG];		//button images
	TTF_Font* font[NROFFONTS];					//all the fonts
	int width_;									//width of screen buffer
	int height_;								//height of screen buffer

	void init();
	void uninit();
	void loadFontsIntoMemory();
	void unloadFontsFromMemory();
	void loadCannonSpritesIntoMemory();
	void unloadCannonSpritesFromMemory();
	void loadButtonSpritesIntoMemory();
	void unloadButtonSpritesFromMemory();
	void loadBackgroundsIntoMemory();
	void unloadBackgroundsFromMemory();
	int getFontNr(const PANZER_FONT& font);
	void drawEmptyButton(int xScreenPos, int yScreenPos, const int& nrOfMiddles, const bool& active);
	SDL_Surface* generateTextSurface(const std::string& text, const PANZER_FONT& font, const SDL_Color& color);
	SDL_Surface* loadImageFromDisc(const std::string&, const bool& transparent = false);
	SDL_Surface* flipImage(SDL_Surface*, const int& flags);
};

#endif
