#include "SDLInclude.h"
#include "GraphicsEngine.h"
#include "Element.h"
#include "SDL_rotozoom.h"
#include "Enums.h"
#include <stdexcept>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*
 * width: Width of screen buffer
 * height: Height of screen buffer
 */
GraphicsEngine::GraphicsEngine(const int& width, const int& height) : screen(NULL), source_image(NULL), width_(width), height_(height)
{
	init();
}

GraphicsEngine::~GraphicsEngine()
{
	uninit();
}

/*
 * Blits all Elements in a vector in given order.
 *
 * element_vector: Referenc to vector of Element
 */
void GraphicsEngine::drawToScreenBuffer(const vector<Element>& element_vector)
{
	if (!element_vector.empty())
	{
		for(vector<Element>::const_iterator it = element_vector.begin();
			it != element_vector.end();
			++it)
		{
			drawToScreenBuffer(*it);
		}
	}
}

/*
 * Blits singel Element to screen buffer.
 * Uses pre-rotated picture if it exists
 * or rotates if needed
 *
 * draw_element: Reference to Element.
 */
void GraphicsEngine::drawToScreenBuffer(const Element& draw_element)
{
	SDL_Rect rcDest;
	rcDest.x = draw_element.get_x();
	rcDest.y = draw_element.get_y();
	rcDest.h = draw_element.get_height();
	rcDest.w = draw_element.get_width();
	int cannonindex = (int)((draw_element.get_angle() / 360.0 * DEGREES)) % DEGREES; //Nödvändig för CANNON

	switch (draw_element.get_imgRef())
	{
	case LEFT_CANNON:
		cannonindex += DEGREES;
	case RIGHT_CANNON:
		rcDest.x -= cannon[cannonindex]->w / 2;
		rcDest.y -= cannon[cannonindex]->h / 2;
		SDL_BlitSurface(cannon[cannonindex], NULL, screen, &rcDest);
		break;
	case GROUND:
		drawRectangle(rcDest.x, screen->h - rcDest.h, rcDest.w, rcDest.h, 0, 255, 0);
		break;
	case CONCRETE:
		drawRectangle(rcDest.x, screen->h - rcDest.h, rcDest.w, rcDest.h, 240, 240, 240);
		break;
	case CANNONBALL:
		rcDest.x -= cannonball->w / 2;
		rcDest.y -= cannonball->h / 2;
		SDL_BlitSurface(cannonball, NULL, screen, &rcDest);
		break;
	default:
		if (draw_element.get_angle() != 0.0)
		{
			SDL_Surface* source = NULL;
			SDL_Rect clip = getClippingRectangle(draw_element.get_imgRef());

			// Skapa ny SDL_Surface
			source = SDL_CreateRGBSurface(source_image->flags,
				clip.w,
				clip.h,
				source_image->format->BitsPerPixel,
				source_image->format->Rmask,
				source_image->format->Gmask,
				source_image->format->Bmask,
				source_image->format->Amask);

			// Om colorkey, sätt colorkey och måla hela bilden "osynlig"
			if (source_image->flags & SDL_SRCCOLORKEY)
			{
				SDL_SetColorKey(source, SDL_SRCCOLORKEY, source_image->format->colorkey);
				SDL_FillRect(source, NULL, source_image->format->colorkey);
			}

			SDL_BlitSurface(source_image, &clip, source, NULL);
			SDL_Surface* rotaded_image = NULL;
			rotaded_image = rotozoomSurface(source, draw_element.get_angle(), 1, 0);
			SDL_FreeSurface(source);
			SDL_SetColorKey(rotaded_image, SDL_SRCCOLORKEY, source_image->format->colorkey);
			SDL_BlitSurface(rotaded_image, NULL, screen, &rcDest);
			SDL_FreeSurface(rotaded_image);
		}
		else
		{
			SDL_Rect clip = getClippingRectangle(draw_element.get_imgRef());
			SDL_BlitSurface(source_image, &clip, screen, &rcDest);
		}
		break;
	}
}

/*
 * Show screnn buffer on screen
 */
void GraphicsEngine::showScreenBufferOnScreen()
{
	SDL_Flip(screen);
}

/*
 * "Tömmer" bufferten genom att fylla den med
 * angiven färg. Färgen ges i form av en unsigned int
 * där de 8 minst signifikanta bitarna represeterar
 * blått, nästa 8 grönt och nästa 8 rött.
 *
 * "Clears" screen buffer by filling it completely
 * with chosen color.
 * 
 * color: 24-bit color
 */
void GraphicsEngine::clearScreenBuffer(const unsigned int& color)
{
	SDL_FillRect(screen, &screen->clip_rect, color);
}

/*
 * Returns rectangle to chosen picture in sprite_sheet
 */
SDL_Rect GraphicsEngine::getClippingRectangle(const PANZER_IMAGE& picture_nr) const
{
	SDL_Rect rect;
	switch (picture_nr)
	{
	case SUN:
		rect.x = 742;
		rect.y = 0;
		rect.w = 154;
		rect.h = 153;
		break;
	}
	return rect;
}

/*
 * Loads picture from disc to mamory and
 * converts it to appropriate depth
 * for fast blitting
 * Handles BMP, PNM (PPM/PGM/PBM), XPM, LBM,
 * PCX, GIF, JPEG, PNG, TGA, och TIFF.
 *
 * filename: Path + filename + extension
 * transparent: True if picture is transparent
 *
 * Retur: Pointer to newly created SDL_Surface
 */
SDL_Surface* GraphicsEngine::loadImageFromDisc(const string& filename, const bool& transparent)
{
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());

	if (!loadedImage)
	{
		cerr << IMG_GetError() << endl;
	}
	
	if (transparent) { // Alphakanalen satt
		optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
	}
	else {
		SDL_SetColorKey(loadedImage, SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 0, 255, 255));
		optimizedImage = SDL_DisplayFormat(loadedImage);
	}
	SDL_FreeSurface(loadedImage);

	return optimizedImage;
}

/*
 * Pre-rotates pictures of Cannon. Ranges from 0 to DEGREES.
 */
void GraphicsEngine::loadCannonSpritesIntoMemory()
{
	SDL_Surface* unrotatedCannon =loadImageFromDisc("cannon.png", true);
	SDL_Surface* flippedCannon = flipImageHorizontally(unrotatedCannon);

	if (!unrotatedCannon) {
		cerr << "cannon.png ej funnen" << endl;
		return;
	}
					
	for (int i = 0; i < DEGREES; ++i)
	{
		cannon[i] = rotozoomSurface(unrotatedCannon, -i * 360.0 / DEGREES, 1, 1);
	}

	for (int j = 0; j < DEGREES; ++j) 
	{
		cannon[DEGREES + j] = rotozoomSurface(flippedCannon, j * 360.0 / DEGREES, 1, 1);
	}
	SDL_FreeSurface(unrotatedCannon);
	SDL_FreeSurface(flippedCannon);
}

/*
 * Free cannon pictures.
 */
void GraphicsEngine::unloadCannonSpritesFromMemory()
{
	for (int i = 0; i < 2*DEGREES; ++i)
	{
		SDL_FreeSurface(cannon[i]);
		cannon[i] = NULL;
	}
}

/*
 * Blits text to screen buffer with black outline.
 *
 * text: Text string.
 * xScreenPos: Top left coren, x.
 * yScreenPos: Top left corner, y.
 * red, green, blue: Color 0 - 255
 * fontName: Font
 */
void GraphicsEngine::drawOutlinedTextToScreenBuffer(const string& text, const int& xScreenPos, const int& yScreenPos, const int& red, const int& green, const int& blue, const PANZER_FONT& fontName)
{
	int x, y;
	int textWidth = 0;
	int textHeight = 0;
	SDL_Surface* sText = NULL;
	SDL_Rect rcDest;

	TTF_SizeText(font[getFontNr(fontName)], text.c_str(), &textWidth, &textHeight);

	// Centrerat
	//xScreenPos = (screen->w - textWidth) / 2;

	// Högerjusterat
	//xScreenPos = (screen->w - textWidth) - xScreenPos;

	SDL_Color textColor = {0, 0, 0, 0};
	sText = TTF_RenderText_Solid(font[getFontNr(fontName)], text.c_str(), textColor);


	for (y = -3; y < 4; ++y)
	{
		for (x = -3; x < 4; ++x)
		{
			rcDest.x = xScreenPos + x;
			rcDest.y = yScreenPos + y;
			SDL_BlitSurface(sText, NULL, screen, &rcDest);
		}
	}

	SDL_FreeSurface(sText);

	SDL_Color textColor2 = {red, green, blue ,0};
	sText = TTF_RenderText_Solid(font[getFontNr(fontName)], text.c_str(), textColor2);
	rcDest.x = xScreenPos;
	rcDest.y = yScreenPos;
	SDL_BlitSurface(sText, NULL, screen, &rcDest);
	SDL_FreeSurface(sText);
}

/*
 * Blits text to screen buffer.
 *
 * text: Text string.
 * xScreenPos: Top left corner, x.
 * yScreenPos: Top left corner, y.
 * red, green, blue: Color 0 - 255
 * fontName: font.
 */
void GraphicsEngine::drawTextToScreenBuffer(const string& text, const int& xScreenPos, const int& yScreenPos, const int& red, const int& green, const int& blue, const PANZER_FONT& fontName)
{
	SDL_Surface* sText;
	SDL_Rect rcDest;

	SDL_Color textColor = {red, green, blue, 0};

	sText = TTF_RenderText_Solid(font[getFontNr(fontName)], text.c_str(), textColor);

	rcDest.x = xScreenPos;
	rcDest.y = yScreenPos;

	SDL_BlitSurface(sText, NULL, screen, &rcDest);

	SDL_FreeSurface(sText);
}

/*
 * Initiates screen buffer, text renderer and loads all pictures and fonts.
 */
void GraphicsEngine::init()
{
	screen = SDL_SetVideoMode(width_, height_, 32, SDL_SWSURFACE);
	
	if (screen == NULL)
	{
		cerr << "Gick ej att initiera SDL screen" << endl;
		return;
	}
	
	if (TTF_Init() == -1)
	{
		cerr << "Gick ej att starta SDL_ttf" << endl;
		return;
	}
	source_image = loadImageFromDisc("sprite_sheet.bmp");
	cannonball = loadImageFromDisc("cannonball.png", true);
	loadButtonSpritesIntoMemory();
	loadCannonSpritesIntoMemory();
	loadFontsIntoMemory();
}

/*
 * Free all pictures, fonts and close text renderer.
 */
void GraphicsEngine::uninit()
{
	SDL_FreeSurface(source_image);
	SDL_FreeSurface(cannonball);
	unloadCannonSpritesFromMemory();
	unloadFontsFromMemory();
	unloadButtonSpritesFromMemory();
	TTF_Quit();
}

/*
 * Free fonts
 */
void GraphicsEngine::unloadFontsFromMemory()
{
	for(int i = 0; i < NROFFONTS; ++i)
	{
		TTF_CloseFont(font[i]);
	}
}

/*
 * Load all fonts to memory
 */
void GraphicsEngine::loadFontsIntoMemory()
{
	font[0] = TTF_OpenFont("lazy.ttf", 32);
	if (!font[0])
	{
		cerr << TTF_GetError() << endl;
	}
	
	font[1] = TTF_OpenFont("lazy.ttf", 26);
	if (!font[1])
	{
		cerr << TTF_GetError() << endl;
	}
	
	font[2] = TTF_OpenFont("paper_cut.ttf", 32);
	if (!font[2])
	{
		cerr << TTF_GetError() << endl;
	}
}

/*
 * Get position of font in array
 *
 * font: Font name.
 */
int GraphicsEngine::getFontNr(const PANZER_FONT& font)
{
	switch (font)
	{
	case LAZY32:
		return 0;
	case LAZY26:
		return 1;
	case PAPER_CUT32:
		return 2;
	default: //Om fonten ej finns, välj den första
		return 0;
	}
}

/*
 * Blit SDL_Surface to screen buffer
 * 
 * image: SDL_Surface* to blit.
 * xScreenPos: Top left corner, x.
 * yScreenPos: Top left corner, y.
 */
void GraphicsEngine::drawSDLSurfaceToScreenBuffer(SDL_Surface *image, const int& xScreenPos, const int& yScreenPos)
{
	SDL_Rect rcDest;
	rcDest.x = xScreenPos;
	rcDest.y = yScreenPos;
	SDL_BlitSurface(image, NULL, screen, &rcDest);
}

/*
 * Load all button pictures to memory.
 */
void GraphicsEngine::loadButtonSpritesIntoMemory()
{
	buttons[0] = loadImageFromDisc("left.png", true);
	buttons[1] = loadImageFromDisc("middle.png", true);
	buttons[2] = loadImageFromDisc("end.png", true);
	buttons[3] = loadImageFromDisc("greyarrow.png", true);
	buttons[4] = loadImageFromDisc("activearrow.png", true);
}

/*
 * Free all button images.
 */
void GraphicsEngine::unloadButtonSpritesFromMemory()
{
	for (int i = 0; i < NROFBUTTONIMG; ++i)
	{
		SDL_FreeSurface(buttons[i]);
	}
}

/*
 * Draw button to screen buffer. Width is adjusted to text width. Alignment
 * left, center and right.
 *
 * text: Button text
 * xScreenPos: Left edge if left aligned, right edge if right aligned and center if centered.
 * yScreenPos: Middle of button.
 * active: True if active button.
 * textfont: Font
 * align: Alignment
 */
void GraphicsEngine::drawButton(const string& text, const int& xScreenPos, const int& yScreenPos, const bool& active, const PANZER_FONT& textfont, const PANZER_ALIGNMENT& align)
{
	int textWidth = 0;
	int textHeight = 0;
	int blitXPos = 0;
	int blitYPos = 0;
	double startWidth = buttons[0]->w;		//Width of first part
	double middleWidth = buttons[1]->w;		//Middle part
	double endWidth = buttons[2]->w;		//End part
	double activeWidth = buttons[3]->w;		//Active part
	double buttonHeight = buttons[0]->h;	//Height
	int i = 0;								//Iteration variable
	SDL_Rect rcDest;						//Button potision
	SDL_Surface* sText = NULL;				//Temporary surface for rendered text

	TTF_SizeText(font[getFontNr(textfont)], text.c_str(), &textWidth, &textHeight);
	
	int nrOfMiddles = (int)(ceil((double)textWidth / middleWidth) + buttonHeight / 2 / middleWidth);

	int totalButtonWidth = (int)(startWidth + nrOfMiddles * middleWidth + activeWidth + endWidth);
	
	switch (align)
	{
	case LEFT:
		blitXPos = xScreenPos;
		break;
	case CENTER:
		blitXPos = xScreenPos - totalButtonWidth / 2;
		break;
	case RIGHT:
		blitXPos = xScreenPos - totalButtonWidth;
		break;
	}

	blitYPos = (int)(yScreenPos -buttonHeight / 2);

	drawEmptyButton(blitXPos, blitYPos, nrOfMiddles, active);

	SDL_Color color = {255, 255, 255};
	sText = generateTextSurface(text, LAZY26, color);
	
	switch (align)
	{
	case LEFT:
		rcDest.x = (int)(xScreenPos + startWidth + nrOfMiddles / 2 * middleWidth - sText->w/2);
		break;
	case CENTER:
		rcDest.x = (int)(xScreenPos - totalButtonWidth / 2 + startWidth + nrOfMiddles * middleWidth / 2 - sText->w / 2);
		break;
	case RIGHT:
		rcDest.x = (int)(xScreenPos - endWidth - activeWidth - nrOfMiddles/2*middleWidth - sText->w/2);
		break;
	}
	
	rcDest.y = yScreenPos - sText->h / 2;

	SDL_BlitSurface(sText, NULL, screen, &rcDest);
	SDL_FreeSurface(sText);
}

/*
 * Blits fix width button.
 *
 * text: Text string in button.
 * xScreenPos: Left edge.
 * yScreenPos: Middle of button
 * width: Width of whole button.
 * active: True if active button.
 * textfont: Font
 * red, green, blue: Color of text, 0 - 255
 */
void GraphicsEngine::drawFixedWidthButton(	const string& text,
											const int& xScreenPos,
											const int& yScreenPos,
											const int& width,
											const bool& active,
											const PANZER_FONT& textfont,
											const int& red,
											const int& green,
											const int& blue)
{
	int nrOfMiddles = (int)((double)(width - buttons[0]->w - buttons[2]->w - buttons[3]->w) / (double)buttons[1]->w);

	drawEmptyButton(xScreenPos, yScreenPos, nrOfMiddles, active);
	SDL_Color color = {red, green, blue};
	SDL_Surface* sText = generateTextSurface(text, textfont, color);

	// Calculate blit position
	int xBlitPos = xScreenPos + nrOfMiddles / 2 * buttons[1]->w - sText->w / 2;
	int yBlitPos = yScreenPos + buttons[0]->h / 2 - sText->h / 2;
	SDL_Rect rcDest;
	rcDest.x = xBlitPos;
	rcDest.y = yBlitPos;
	SDL_BlitSurface(sText, NULL, screen, &rcDest);
	SDL_FreeSurface(sText);
}

/*
 * Blit text to newly created SDL_Surface
 *
 * text: Text string
 * fontname: Font.
 * color: Color of text.
 *
 * Retur: Pointer to newly created SDL_Surface.
 */
SDL_Surface* GraphicsEngine::generateTextSurface(const string& text, const PANZER_FONT& fontname, const SDL_Color& color)
{
	SDL_Surface* sText = NULL;
	sText = TTF_RenderText_Solid(font[getFontNr(fontname)], text.c_str(), color);
	return sText;
}

/*
 * Blits button without text.
 *
 * xScreenPos: Top left corner, x.
 * yScreenPos: Top left corner, y.
 * nrOfMiddles: Number of middle sections.
 * active: True if active button.
 */
void GraphicsEngine::drawEmptyButton(int xScreenPos, int yScreenPos, const int& nrOfMiddles, const bool& active)
{
	SDL_Rect rcDest;
	rcDest.x = xScreenPos;
	rcDest.y = yScreenPos;

	SDL_BlitSurface(buttons[0], NULL, screen, &rcDest);
	xScreenPos += buttons[0]->w;
	rcDest.x =xScreenPos;

	for (int i = 0; i < nrOfMiddles; ++i) {
		SDL_BlitSurface(buttons[1], NULL, screen, &rcDest);
		xScreenPos += buttons[1]->w;
		rcDest.x =xScreenPos;
	}

	if (active) {
		SDL_BlitSurface(buttons[4], NULL, screen, &rcDest);
		xScreenPos += buttons[4]->w;
	}
	else {
		SDL_BlitSurface(buttons[3], NULL, screen, &rcDest);
		xScreenPos += buttons[3]->w;
	}

	rcDest.x = xScreenPos;
	SDL_BlitSurface(buttons[2], NULL, screen, &rcDest);
}

/*
 * Blits rectangle with chosen color.
 * 
 * xScreenPos: Top left corner, x.
 * yScreenPos: Top left corner, y.
 * width: Width in pixels.
 * height: Height in pixels.
 * red, green, blue: Color 0 - 255.
 */
void GraphicsEngine::drawRectangle(const int &xScreenPos, const int &yScreenPos, const int &width, const int &height, const int& red, const int& green, const int& blue)
{
	SDL_Rect rect;
	rect.x = xScreenPos;
	rect.y = yScreenPos;
	rect.w = width;
	rect.h = height;
	SDL_Color color = {red, green, blue};
	SDL_FillRect(screen, &rect, color.r << 16 | color.g << 8 | color.b << 0);
}

/*
 * Blits all Elements in vector of Element*.
 * 
 * elemVector: Reference to vector of Element*.
 */
void GraphicsEngine::drawToScreenBuffer(const vector<Element*>& elemVector)
{
	for (vector<Element*>::const_iterator it = elemVector.begin(); it != elemVector.end(); ++it)
	{
		if (!(*it)) {
			cerr << "Trying to blit NULL pointer" << endl;
			return;
		}
		drawToScreenBuffer(**it);
	}
}

void GraphicsEngine::drawToScreenBuffer(const vector<MovableElement*>& elemVector)
{
	for (vector<MovableElement*>::const_iterator it = elemVector.begin(); it != elemVector.end(); ++it)
	{
		drawToScreenBuffer(**it);
	}
}

/*
 * Flips an SDL_Surface horizontally on a newly created SDL_Surface
 *
 * originalImage: Picture to flip
 *
 * Retur: Pointer to new image.
 */
SDL_Surface* GraphicsEngine::flipImageHorizontally(SDL_Surface* originalImage)
{
	SDL_Surface* flippedImage = NULL;

	flippedImage = SDL_CreateRGBSurface(	originalImage->flags,
									originalImage->w,
									originalImage->h,
									originalImage->format->BitsPerPixel,
									originalImage->format->Rmask,
									originalImage->format->Gmask,
									originalImage->format->Bmask,
									(originalImage->flags & SDL_SRCCOLORKEY) ? 0 : originalImage->format->Amask);
	
	if (SDL_MUSTLOCK(originalImage)) {
		SDL_LockSurface(originalImage);
	}

	Uint32* sourcePixels = (Uint32*)originalImage->pixels;
	Uint32* targetPixels = (Uint32*)flippedImage->pixels;

	for (int x = 0, rx = flippedImage->w - 1; x < flippedImage->w; ++x, --rx) {
		for(int y = 0; y < flippedImage->h; ++y) {
			targetPixels[y * flippedImage->w + rx] = sourcePixels[y * originalImage->w + x];
		}
	}

	if (SDL_MUSTLOCK(originalImage)) {
		SDL_UnlockSurface(originalImage);
	}

	if (originalImage->flags & SDL_SRCCOLORKEY) {
		SDL_SetColorKey(flippedImage, SDL_SRCCOLORKEY, originalImage->format->colorkey);
	}

	return flippedImage;
}

/*
 * Draws a colored bar on screen buffer.
 *
 * xScreenPos: Top left corner.
 * yScreenPos: Top left corner.
 * width: Width in pixels.
 * height: Height in pixels.
 * percentage: Percentage of bar to fill.
 */
void GraphicsEngine::drawPowerBarToScreenBuffer(const int& xScreenPos, const int& yScreenPos, const int& width, const int& height, const int& percentage)
{
	SDL_Rect rcDest;
	
	rcDest.x = xScreenPos;
	rcDest.y = yScreenPos;
	rcDest.w = 1;
	rcDest.h = height;

	rcDest.w = 1;

	for (int i = 0; i < width  * percentage / 100.0; ++i, ++rcDest.x)
	{
		SDL_FillRect(screen, &rcDest,  (i * 255 / width) << 16 | (255 - i * 255 / width) << 8 | 0 << 0 );
	}
}