#include "GraphicsEngine.h"
#include "Element.h"
#include "SDL_rotozoom.h"
#include "Enums.h"
#include <stdexcept>
#include <vector>
#include <string>

using namespace std;


GraphicsEngine::GraphicsEngine(const int& width, const int& height) : screen(NULL), source_image(NULL)
{
	screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
	if (screen == NULL)
		throw logic_error("Gick ej att initiera SDL screen");
	source_image = load_image("sprite_sheet.bmp");
}

GraphicsEngine::~GraphicsEngine()
{
	SDL_FreeSurface(source_image);
}

bool GraphicsEngine::draw(vector<Element>& element_vector)
{
	for(vector<Element>::iterator it = element_vector.begin();
		it != element_vector.end();
		++it)
	{
		draw(*it);
	}
	
	return true;
}

bool GraphicsEngine::draw(Element& draw_element)
{
	if (draw_element.get_angle() != 0.0) {
		SDL_Surface* source = NULL;
		SDL_Rect clip = get_clipping_rect(draw_element.get_image());
		source = SDL_CreateRGBSurfaceFrom(source_image->pixels, clip.w, clip.h, source_image->format->BitsPerPixel, source_image->pitch, source_image->format->Rmask, source_image->format->Gmask, source_image->format->Bmask, source_image->format->Amask);
		SDL_BlitSurface(source_image, NULL, source, NULL);
		SDL_Surface* rotaded_image = NULL;
		rotaded_image = rotozoomSurface(source, draw_element.get_angle(), 1, 1);
		SDL_FreeSurface(source);
		SDL_BlitSurface(rotaded_image, NULL, screen, &draw_element.get_position_rect());
		SDL_FreeSurface(rotaded_image);
	}
	else {
		SDL_BlitSurface(source_image, &get_clipping_rect(draw_element.get_image()), screen, &draw_element.get_position_rect());
	}
	return true;
}

void GraphicsEngine::update_screen()
{
	SDL_Flip(screen);
}

void GraphicsEngine::clear()
{
	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
}

SDL_Rect GraphicsEngine::get_clipping_rect(PANZER_IMAGE& picture_nr)
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
		rect.h = 277;
		break;
	}
	return rect;
}

SDL_Surface* GraphicsEngine::load_image(string filename)
{
	SDL_Surface* loadedimage = NULL;
	SDL_Surface* optimizedimage = NULL;

	loadedimage = SDL_LoadBMP(filename.c_str());

	if (loadedimage != NULL) {
		optimizedimage = SDL_DisplayFormat(loadedimage);
	}
	SDL_FreeSurface(loadedimage);
	return optimizedimage;
}