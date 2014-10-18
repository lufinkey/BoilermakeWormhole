
#include <SDL.h>
#undef main

#include <SFML/Network.hpp>
#include <iostream>
#include "String.h"

#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#pragma comment(lib, "ws2_32.lib")
#endif // SFML_STATIC

int main(int argc, char* argv[])
{
	//TODO add bending of space and time

	SDL_Window* window;
	SDL_Renderer* renderer;

	if(!SDL_WasInit(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER))
	{
		if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) < 0)
		//if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			return 1;
		}
	}

	window = SDL_CreateWindow(NULL, 0, 0, 300, 300, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


}