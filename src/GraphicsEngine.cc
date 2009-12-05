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
	SDL_Rect destinationRectangle;
	destinationRectangle.x = draw_element.get_x();
	destinationRectangle.y = draw_element.get_y();

	if (draw_element.get_imgRef() == CANNON)
	{
		int index = (int)draw_element.get_angle() % DEGREES;
		destinationRectangle.x -= cannon[index]->w / 2;
		destinationRectangle.y-= cannon[index]->h / 2;
		SDL_BlitSurface(cannon[index], NULL, screen, &destinationRectangle);
	}
	else
	{
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
			SDL_BlitSurface(rotaded_image, NULL, screen, &destinationRectangle);
			SDL_FreeSurface(rotaded_image);
		}
		else
		{
			SDL_Rect clip = getClippingRectangle(draw_element.get_imgRef());
			SDL_BlitSurface(source_image, &clip, screen, &destinationRectangle);
		}
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
void GraphicsEngine::clearScreenBuffer(const unsigned int color)
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
SDL_Surface* GraphicsEngine::loadImageFromDisc(const string& filename)
{
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());

	if (loadedImage != NULL) {
		SDL_SetColorKey(loadedImage, SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 0, 255, 255));
		optimizedImage = SDL_DisplayFormat(loadedImage);

	}
	else {
		cerr << IMG_GetError() << endl;
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
	SDL_Surface* unrotatedCannon = IMG_Load("cannon.png");
	/*
	SDL_Surface* unrotatedCannon = SDL_CreateRGBSurface(
		source_image->flags,
		getClippingRectangle(CANNON).w,
		getClippingRectangle(CANNON).h,
		source_image->format->BitsPerPixel,
		source_image->format->Rmask,
		source_image->format->Gmask,
		source_image->format->Bmask,
		source_image->format->Amask);
	*/

	//SDL_SetColorKey(unrotatedCannon, SDL_SRCCOLORKEY, source_image->format->colorkey);
	//SDL_FillRect(unrotatedCannon, NULL, source_image->format->colorkey);
	//SDL_FillRect(unrotatedCannon, NULL, SDL_MapRGBA(screen->format, 0, 0, 0, 0));
	//SDL_BlitSurface(source_image, &getClippingRectangle(CANNON), unrotatedCannon, NULL);
							
	for (int i = 0; i < DEGREES; ++i)
	{
		cannon[i] = rotozoomSurface(unrotatedCannon, -i, 1, 1);
		SDL_SetColorKey(cannon[i], SDL_SRCCOLORKEY, source_image->format->colorkey);
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
void GraphicsEngine::drawOutlinedTextToScreenBuffer(const string& text, int xScreenPos, int yScreenPos, int red, int green, int blue, int fontIndex)
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
void GraphicsEngine::drawTextToScreenBuffer(const string& text, int xScreenPos, int yScreenPos, int red, int green, int blue, int fontIndex)
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
	//loadCannonSpritesIntoMemory();
	loadFontsIntoMemory();
}

/*
 * Frig�r minne
 */
void GraphicsEngine::uninit()
{
	SDL_FreeSurface(source_image);
	//unloadCannonSpritesFromMemory();
	unloadFontsFromMemory();
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
}

/*
 * Ritar SDL_Surface till buffert
 */
void GraphicsEngine::drawSDLSurfaceToScreenBuffer(SDL_Surface *image, int xScreenPos, int yScreenPos)
{
	SDL_Rect rcDest;
	rcDest.x = xScreenPos;
	rcDest.y = yScreenPos;
	SDL_BlitSurface(image, NULL, screen, &rcDest);
}
