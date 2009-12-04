#ifndef SDLINCLUDE_
#define SDLINCLUDE_

/*
 * Include this to include the SDL library
 * 
 */

/*
 * Platform
 * WINDOWS
 * MAC
 * LINUX (both unix and linux)
 */
 
 #undef MAC
 #undef LINUX
 #define WINDOWS

#ifdef WINDOWS
	#include "SDL.h"
	#include "SDL_image.h"
	#include "SDL_ttf.h"
#endif

#ifdef LINUX
	#include "SDL/SDL.h"
	#include "SDL/SDL_image.h"
	#include "SDL/SDL_ttf.h"
#endif

#endif /*SDLINCLUDE_*/
