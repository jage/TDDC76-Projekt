#include "GraphicsEngine.h"
#include "Element.h"
#include "SDL_rotozoom.h"
#include "Enums.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <stdexcept>
#include <vector>
#include <string>
#include <iostream>

using namespace std;


GraphicsEngine::GraphicsEngine(const int& width, const int& height) : screen(NULL), source_image(NULL)
{
	// Initiera en SDL-yta
	screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
	if (screen == NULL)
		throw logic_error("Gick ej att initiera SDL screen");

	// starta SDL_ttf
	if (TTF_Init() == -1)
		cerr << "Gick ej att starta SDL_ttf" << endl;

	// Ladda in bilderna
	source_image = loadImageFromDisc("sprite_sheet.bmp");
	init();
}

GraphicsEngine::~GraphicsEngine()
{
	// Frigör alla bilder och fonter
	uninit();
	SDL_FreeSurface(source_image);
	TTF_Quit();
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
 * Finns förroterade bilder används dessa
 * annars roteras bilder när de behövs
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
			SDL_Rect clip = get_clipping_rect(draw_element.get_imgRef());
			source = SDL_CreateRGBSurfaceFrom(source_image->pixels,
												clip.w,
												clip.h,
												source_image->format->BitsPerPixel,
												source_image->pitch,
												source_image->format->Rmask,
												source_image->format->Gmask,
												source_image->format->Bmask,
												source_image->format->Amask);
			SDL_BlitSurface(source_image, NULL, source, NULL);
			SDL_Surface* rotaded_image = NULL;
			rotaded_image = rotozoomSurface(source, draw_element.get_angle(), 1, 1);
			SDL_FreeSurface(source);
			SDL_BlitSurface(rotaded_image, NULL, screen, &destinationRectangle);
			SDL_FreeSurface(rotaded_image);
		}
		else
		{
			SDL_BlitSurface(source_image, &get_clipping_rect(draw_element.get_imgRef()), screen, &destinationRectangle);
		}
	}
}

void GraphicsEngine::showScreenBufferOnScreen()
{
	SDL_Flip(screen);
}

/*
 * "Tömmer" bufferten genom att fylla den med
 * angiven färg. Färgen ges i form av en unsigned int
 * där de 8 minst signifikanta bitarna represeterar
 * blått, nästa 8 grönt och nästa 8 rött.
 */
void GraphicsEngine::clearScreenBuffer(const unsigned int color)
{
	SDL_FillRect(screen, &screen->clip_rect, color);
}

/*
 * "Tömmer" bufferten genom att fylla den med
 * vit färg.
 */
void GraphicsEngine::clearScreenBuffer()
{
	clearScreenBuffer(0xff << 16 | 0xff << 8 | 0xff << 0);
}

/*
 * Returnerar rektangeln där respektive bild finns i
 * sprite_sheet
 */
SDL_Rect GraphicsEngine::get_clipping_rect(const PANZER_IMAGE& picture_nr) const
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
		rect.x = 741;
		rect.y = 0;
		rect.w = 155;
		rect.h = 154;
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
 * Laddar in bild från disk och konverterar
 * den till rätt format för snabb blittning.
 * Klarar BMP, PNM (PPM/PGM/PBM), XPM, LBM,
 * PCX, GIF, JPEG, PNG, TGA, och TIFF.
 */
SDL_Surface* GraphicsEngine::loadImageFromDisc(const string& filename)
{
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());

	if (loadedImage != NULL) {
		optimizedImage = SDL_DisplayFormat(loadedImage);
	}
	else
	{
		cerr << IMG_GetError() << endl;
	}
	SDL_FreeSurface(loadedImage);
	return optimizedImage;
}

void GraphicsEngine::loadCannonSpritesIntoMemory()
{
	SDL_Surface* unrotatedCannon = SDL_CreateRGBSurface(source_image->flags,
		get_clipping_rect(CANNON).w,
		get_clipping_rect(CANNON).h,
		source_image->format->BitsPerPixel,
		source_image->format->Rmask,
		source_image->format->Gmask,
		source_image->format->Bmask,
		source_image->format->Amask);

	SDL_BlitSurface(source_image, &get_clipping_rect(CANNON), unrotatedCannon, NULL);
							
	for (int i = 0; i < DEGREES; ++i)
	{
		cannon[i] = rotozoomSurface(unrotatedCannon, i, 1, 1);
	}
	SDL_FreeSurface(unrotatedCannon);
}

void GraphicsEngine::unloadCannonSpritesFromMemory()
{
	for (int i = 0; i < DEGREES; ++i)
	{
		SDL_FreeSurface(cannon[i]);
		cannon[i] = NULL;
	}
}

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

	// Högerjusterat
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



void GraphicsEngine::init()
{
	loadCannonSpritesIntoMemory();
	loadFontsIntoMemory();
}

void GraphicsEngine::uninit()
{
	unloadCannonSpritesFromMemory();
	unloadFontsFromMemory();
}

void GraphicsEngine::unloadFontsFromMemory()
{
	for(int i = 0; i < NROFFONTS; ++i)
	{
		TTF_CloseFont(font[i]);
	}
}

void GraphicsEngine::loadFontsIntoMemory()
{
	font[0] = TTF_OpenFont("lazy.ttf", 32);
	if (!font[0])
	{
		cerr << TTF_GetError() << endl;
	}
}

