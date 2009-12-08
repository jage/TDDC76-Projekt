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


GraphicsEngine::GraphicsEngine(const int& width, const int& height) : screen(NULL), source_image(NULL), width_(width), height_(height)
{
	init();
}

GraphicsEngine::~GraphicsEngine()
{
	uninit();
}

/*
 * Ritar ut alla element i vektorn till bufferten i den ordning ligger i vektorn
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
 * Ritar ut ett enstaka element till bufferten
 * Finns f�rroterade bilder anv�nds dessa
 * annars roteras bilder n�r de beh�vs
 */

void GraphicsEngine::drawToScreenBuffer(const Element& draw_element)
{
	SDL_Rect rcDest;
	rcDest.x = draw_element.get_x();
	rcDest.y = draw_element.get_y();
	rcDest.h = draw_element.get_height();
	rcDest.w = draw_element.get_width();
	int index = (int)draw_element.get_angle() % DEGREES; //Nödvändig för CANNON

	switch (draw_element.get_imgRef())
	{
	case CANNON:
		rcDest.x -= cannon[index]->w / 2;
		rcDest.y -= cannon[index]->h / 2;
		SDL_BlitSurface(cannon[index], NULL, screen, &rcDest);
		break;
	case GROUND:
		drawRectangle(rcDest.x, screen->h - rcDest.h, rcDest.w, rcDest.h, 0, 255, 0);
		break;
	case CONCRETE:
		drawRectangle(rcDest.x, screen->h - rcDest.h, rcDest.w, rcDest.h, 240, 240, 240);
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

			// Om colorkey, s�tt colorkey och m�la hela bilden "osynlig"
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

void GraphicsEngine::showScreenBufferOnScreen()
{
	SDL_Flip(screen);
}

/*
 * "T�mmer" bufferten genom att fylla den med
 * angiven f�rg. F�rgen ges i form av en unsigned int
 * d�r de 8 minst signifikanta bitarna represeterar
 * bl�tt, n�sta 8 gr�nt och n�sta 8 r�tt.
 */
void GraphicsEngine::clearScreenBuffer(const unsigned int& color)
{
	SDL_FillRect(screen, &screen->clip_rect, color);
}

/*
 * "T�mmer" bufferten genom att fylla den med
 * vit f�rg.
 */
void GraphicsEngine::clearScreenBuffer()
{
	clearScreenBuffer(0xff << 16 | 0xff << 8 | 0xff << 0);
}

/*
 * Returnerar rektangeln d�r respektive bild finns i
 * sprite_sheet
 */
SDL_Rect GraphicsEngine::getClippingRectangle(const PANZER_IMAGE& picture_nr) const
{
	SDL_Rect rect;
	switch (picture_nr)
	{
	case CANNONBALL:
		rect.x = 0;
		rect.y = 0;
		rect.w = 250;
		rect.h = 277;
		break;
	case SUN:
		rect.x = 742;
		rect.y = 0;
		rect.w = 154;
		rect.h = 153;
		break;
	case CANNON:
		rect.x = 253;
		rect.y = 0;
		rect.w = 239;
		rect.h = 184;
		break;
	}
	return rect;
}

/*
 * Laddar in bild fr�n disk och konverterar
 * den till r�tt format f�r snabb blittning.
 * Klarar BMP, PNM (PPM/PGM/PBM), XPM, LBM,
 * PCX, GIF, JPEG, PNG, TGA, och TIFF.
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
 * F�rroterar alla bilder till cannon fr�n
 * 0 upp till DEGREES. Bilden h�mtas fr�n
 * bilden dit getClippingRectangle() pekar.
 */
void GraphicsEngine::loadCannonSpritesIntoMemory()
{
	SDL_Surface* unrotatedCannon =loadImageFromDisc("cannon.png", true);

	if (!unrotatedCannon) {
		cerr << "cannon.png ej funnen" << endl;
	}
					
	for (int i = 0; i < DEGREES; ++i)
	{
		cannon[i] = rotozoomSurface(unrotatedCannon, -i, 1, 1);
	}
	SDL_FreeSurface(unrotatedCannon);
}

/*
 * Frig�r minnet fr�n cannon
 */
void GraphicsEngine::unloadCannonSpritesFromMemory()
{
	for (int i = 0; i < DEGREES; ++i)
	{
		SDL_FreeSurface(cannon[i]);
		cannon[i] = NULL;
	}
}

/*
 * Skriver ut �nskad text till bufferten med svart kant
 * runt om. F�rg v�ljs fr�n 0-255 i respektive r�tt,
 * gr�nt och bl�tt.
 */
void GraphicsEngine::drawOutlinedTextToScreenBuffer(const string& text, const int& xScreenPos, const int& yScreenPos, const int& red, const int& green, const int& blue, const int& fontIndex)
{
	int x, y;
	int textWidth = 0;
	int textHeight = 0;
	SDL_Surface* sText = NULL;
	SDL_Rect rcDest;

	if (fontIndex > NROFFONTS)
	{
		cerr << "GraphicsEngine::drawOutlinedTextToScreenBuffer: fontIndex out of range" << endl;
		return;
	}

	TTF_SizeText(font[fontIndex], text.c_str(), &textWidth, &textHeight);

	// Centrerat
	//xScreenPos = (screen->w - textWidth) / 2;

	// H�gerjusterat
	//xScreenPos = (screen->w - textWidth) - xScreenPos;

	SDL_Color textColor = {0, 0, 0, 0};
	sText = TTF_RenderText_Solid(font[fontIndex], text.c_str(), textColor);


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
	sText = TTF_RenderText_Solid(font[fontIndex], text.c_str(), textColor2);
	rcDest.x = xScreenPos;
	rcDest.y = yScreenPos;
	SDL_BlitSurface(sText, NULL, screen, &rcDest);
	SDL_FreeSurface(sText);
}

/*
 * Skriver ut �nskad text till bufferten utan svart kant
 * runt om. F�rg v�ljs fr�n 0-255 i respektive r�tt,
 * gr�nt och bl�tt.
 */
void GraphicsEngine::drawTextToScreenBuffer(const string& text, const int& xScreenPos, const int& yScreenPos, const int& red, const int& green, const int& blue, const int& fontIndex)
{
	int textWidth = 0;
	int textHeight = 0;
	SDL_Surface* sText;
	SDL_Rect rcDest;

	if (fontIndex > NROFFONTS)
	{
		cerr <<  "GraphicsEngine::drawOutlinedTextToScreenBuffer: fontIndex out of range" << endl;
		return;
	}

	SDL_Color textColor = {red, green, blue, 0};

	sText = TTF_RenderText_Solid(font[fontIndex], text.c_str(), textColor);

	rcDest.x = xScreenPos;
	rcDest.y = yScreenPos;

	SDL_BlitSurface(sText, NULL, screen, &rcDest);

	SDL_FreeSurface(sText);
}

/*
 * Initierar alla bilder och fonter
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
	loadButtonSpritesIntoMemory();
	loadCannonSpritesIntoMemory();
	loadFontsIntoMemory();
}

/*
 * Frig�r minne
 */
void GraphicsEngine::uninit()
{
	SDL_FreeSurface(source_image);
	unloadCannonSpritesFromMemory();
	unloadFontsFromMemory();
	unloadButtonSpritesFromMemory();
	TTF_Quit();
}

/*
 * Frig�r minnet f�r alla fonter.
 */
void GraphicsEngine::unloadFontsFromMemory()
{
	for(int i = 0; i < NROFFONTS; ++i)
	{
		TTF_CloseFont(font[i]);
	}
}

/*
 * L�ser in alla fonter i minnet.
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
}

int GraphicsEngine::getFontNr(const PANZER_FONT& font)
{
	int returnval = 0;
	switch (font)
	{
	case LAZY32:
		return 0;
	case LAZY26:
		return 1;
	default:
		return 0;
	}
}

/*
 * Ritar SDL_Surface till buffert
 */
void GraphicsEngine::drawSDLSurfaceToScreenBuffer(SDL_Surface *image, const int& xScreenPos, const int& yScreenPos)
{
	SDL_Rect rcDest;
	rcDest.x = xScreenPos;
	rcDest.y = yScreenPos;
	SDL_BlitSurface(image, NULL, screen, &rcDest);
}

void GraphicsEngine::loadButtonSpritesIntoMemory()
{
	buttons[0] = loadImageFromDisc("left.png", true);
	buttons[1] = loadImageFromDisc("middle.png", true);
	buttons[2] = loadImageFromDisc("end.png", true);
	buttons[3] = loadImageFromDisc("greyarrow.png", true);
	buttons[4] = loadImageFromDisc("activearrow.png", true);
}

void GraphicsEngine::unloadButtonSpritesFromMemory()
{
	for (int i = 0; i < NROFBUTTONIMG; ++i)
	{
		SDL_FreeSurface(buttons[i]);
	}
}

void GraphicsEngine::drawButton(const string& text, const int& xScreenPos, const int& yScreenPos, const bool& active, const PANZER_FONT& textfont, const PANZER_ALIGNMENT& align)
{
	int textWidth = 0;
	int textHeight = 0;
	int blitXPos = 0;
	int blitYPos = 0;
	double startWidth = buttons[0]->w;		//Bredden av första biten
	double middleWidth = buttons[1]->w;		//Mittenbiten
	double endWidth = buttons[2]->w;		//Slutbiten
	double activeWidth = buttons[3]->w;		//aktivbiten
	double buttonHeight = buttons[0]->h;	//höjden
	int i = 0;								//iterationsvariabel
	SDL_Rect rcDest;						//position av knappen
	SDL_Surface* sText = NULL;				//tillfällig yta för texten

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

	// Beräkna blitposition
	int xBlitPos = xScreenPos + nrOfMiddles / 2 * buttons[1]->w - sText->w / 2;
	int yBlitPos = yScreenPos + buttons[0]->h / 2 - sText->h / 2;
	SDL_Rect rcDest;
	rcDest.x = xBlitPos;
	rcDest.y = yBlitPos;
	SDL_BlitSurface(sText, NULL, screen, &rcDest);
	SDL_FreeSurface(sText);
}

SDL_Surface* GraphicsEngine::generateTextSurface(const string& text, const PANZER_FONT& fontname, const SDL_Color& color)
{
	SDL_Surface* sText = NULL;
	sText = TTF_RenderText_Solid(font[getFontNr(fontname)], text.c_str(), color);
	return sText;
}

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

void GraphicsEngine::drawRectangle(const int &xScreenPos, const int &yScreenPos, const int &width, const int &height, const int& red, const int& green, const int& blue)
{
	SDL_Rect rect;
	rect.x = xScreenPos;
	rect.y = yScreenPos;
	rect.w = width;
	rect.h = height;
	SDL_FillRect(screen, &rect, red << 16 | green << 8 | blue << 0);
}

void GraphicsEngine::drawToScreenBuffer(const vector<Element*>& elemVector)
{
	for (vector<Element*>::const_iterator it = elemVector.begin(); it != elemVector.end(); ++it)
	{
		drawToScreenBuffer(*(*it));
	}
}
