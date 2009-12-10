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
 * width: Bredd av skärmbufferten
 * height: Höjd av skärmbufferten
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
 * Ritar ut alla element i vektorn till bufferten i den ordning ligger i vektorn
 *
 * element_vector: Referens till vektor med Element
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
 *
 * draw_element: Referens till Element att rita.
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
 * Visar bufferten på skärmen
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
 * color: 24-bitars färg
 */
void GraphicsEngine::clearScreenBuffer(const unsigned int& color)
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
	}
	return rect;
}

/*
 * Laddar in bild från disk och konverterar
 * den till rätt format för snabb blittning.
 * Klarar BMP, PNM (PPM/PGM/PBM), XPM, LBM,
 * PCX, GIF, JPEG, PNG, TGA, och TIFF.
 *
 * filename: Sökväg och filname inkl filändelse
 * transparent: True om bilden har transparenta delar
 *
 * Retur: Pekare till laddad SDL_Surface
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
 * Förroterar alla bilder till cannon från
 * 0 upp till DEGREES.
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
 * Frigör minnet från bilderna till cannon
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
 * Skriver ut önskad text till bufferten med svart kant
 * runt om. Färg väljs från 0-255 i respektive rött,
 * grönt och blått.
 *
 * text: Textsträng
 * xScreenPos: Övre vänstra hörnet, x-led
 * yScreenPos: Övre vänstra hörnet, y-led
 * red, green, blue: Färg 0 - 255
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
 * Skriver ut önskad text till bufferten utan svart kant
 * runt om. färg väljs från 0-255 i respektive rött,
 * grönt och blått.
 *
 * text: Textsträng
 * xScreenPos: Övre vänstra hörnet, x-led
 * yScreenPos: Övre vänstra hörnet, y-led
 * red, green, blue: Färg 0 - 255
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
 * Initierar bufferten och textrenderaren samt alla bilder och fonter.
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
 * Frigör allt allokerat minne och stänger ned textrenderaren
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
 * Frigör minnet för alla fonter.
 */
void GraphicsEngine::unloadFontsFromMemory()
{
	for(int i = 0; i < NROFFONTS; ++i)
	{
		TTF_CloseFont(font[i]);
	}
}

/*
 * Läser in alla fonter i minnet.
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

/*
 * Tar fram ordingstalet för en viss font
 *
 * font: Fontnamn
 */
int GraphicsEngine::getFontNr(const PANZER_FONT& font)
{
	switch (font)
	{
	case LAZY32:
		return 0;
	case LAZY26:
		return 1;
	default: //Om fonten ej finns, välj den första
		return 0;
	}
}

/*
 * Ritar SDL_Surface till buffert
 * 
 * image: Pekare till SDL_Surface att rita
 * xScreenPos: Översta vänstra hörnet i bilden, x-led
 * yScreenPos: Översta vänstra hörnet i bilden, y-led
 */
void GraphicsEngine::drawSDLSurfaceToScreenBuffer(SDL_Surface *image, const int& xScreenPos, const int& yScreenPos)
{
	SDL_Rect rcDest;
	rcDest.x = xScreenPos;
	rcDest.y = yScreenPos;
	SDL_BlitSurface(image, NULL, screen, &rcDest);
}

/*
 * Läser in alla knappar i minnet
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
 * Frigör minnet från alla knappbilder
 */
void GraphicsEngine::unloadButtonSpritesFromMemory()
{
	for (int i = 0; i < NROFBUTTONIMG; ++i)
	{
		SDL_FreeSurface(buttons[i]);
	}
}

/*
 * Ritar en knapp med automatisk bredd. Justering kan väljas mellan vänsterjusterad, högerjusterad och centrerad
 *
 * text: Knapptext
 * xScreenPos: Vänstra kanten om vänsterjusterad, högra kanten om högerjusterad och mitten om centrerad.
 * yScreenPos: Mitten av knappen i höjdled
 * active: True om knappen aktiv
 * textfont: Font
 * align: Justering
 */
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

/*
 * Ritar knapp med text med fast knappbredd
 *
 * text: Textsträng i knappen
 * xScreenPos: Vänstra kanten av knappen
 * yScreenPos: Y-koordinat för mitten av knappen
 * width: Bredd av hela knappen
 * active: True om knappen äv aktiv
 * textfont: Font
 * red, green, blue: Färg på texten, 0 - 255
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

	// Beräkna blitposition
	int xBlitPos = xScreenPos + nrOfMiddles / 2 * buttons[1]->w - sText->w / 2;
	int yBlitPos = yScreenPos + buttons[0]->h / 2 - sText->h / 2;
	SDL_Rect rcDest;
	rcDest.x = xBlitPos;
	rcDest.y = yBlitPos;
	SDL_BlitSurface(sText, NULL, screen, &rcDest);
	SDL_FreeSurface(sText);
}

/*
 * Renderar en text på nyskapad SDL_Surface
 *
 * text: Textsträng att rendera
 * fontname: Font att använda. Väljs ur PANZER_FONT.
 * color: Färg på texten
 *
 * Retur: Pekare till skapad SDL_Surface
 */
SDL_Surface* GraphicsEngine::generateTextSurface(const string& text, const PANZER_FONT& fontname, const SDL_Color& color)
{
	SDL_Surface* sText = NULL;
	sText = TTF_RenderText_Solid(font[getFontNr(fontname)], text.c_str(), color);
	return sText;
}

/*
 * Ritar ut en knapp utan text.
 *
 * xScreenPos: Övre vänstra hörnet i x-led.
 * yScreenPos: Övre vänstra hörnet i y-led.
 * nrOfMiddles: Antalet mittensektioner.
 * active: True om knappen ska vara aktiv.
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
 * Ritar rektangel med vald färg
 * 
 * xScreenPos: Övre vänstra hörnet i x-led.
 * yScreenPos: Övre vänstra hörnet i y-led.
 * width: Bredd i antal pixlar.
 * height: Höjd i antal pixlar.
 * red, green, blue: Färg 0 - 255.
 */
void GraphicsEngine::drawRectangle(const int &xScreenPos, const int &yScreenPos, const int &width, const int &height, const int& red, const int& green, const int& blue)
{
	SDL_Rect rect;
	rect.x = xScreenPos;
	rect.y = yScreenPos;
	rect.w = width;
	rect.h = height;
	SDL_FillRect(screen, &rect, red << 16 | green << 8 | blue << 0);
}

/*
 * Ritar alla Element i en vektor med Element*.
 * 
 * elemVector: referens till vektor med Element*
 */
void GraphicsEngine::drawToScreenBuffer(const vector<Element*>& elemVector)
{
	for (vector<Element*>::const_iterator it = elemVector.begin(); it != elemVector.end(); ++it)
	{
		drawToScreenBuffer(*(*it));
	}
}

/*
 * Flippar en SDL_Surface horizontellt på en nyskapad SDL_Suface.
 *
 * originalImage: Bild att vända.
 *
 * Retur: Pekare till nya bilden
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



