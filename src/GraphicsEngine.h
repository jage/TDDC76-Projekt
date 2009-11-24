#ifndef GRAPHICSENGINE_H_
#define GRAPHICSENGINE_H_

#include "SDL.h"
#include "Element.h"
#include "Enums.h"
#include <vector>
#include <string>

class GraphicsEngine
{
public:
	GraphicsEngine(int = 640, int = 480);
	~GraphicsEngine();

	bool draw(std::vector<Element>&);
	bool draw(Element&);
	void clear();
	void update_screen();
	SDL_Rect get_clipping_rect(PANZER_IMAGE);
	//bool load_image(string);
private:
	SDL_Surface* screen;
	SDL_Surface* source_image;

	SDL_Surface* load_image(std::string);
};

#endif