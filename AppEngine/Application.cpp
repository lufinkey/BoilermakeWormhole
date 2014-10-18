#include "Application.h"

namespace AppEngine
{
	unsigned int Application::windowWidth = 640;
	unsigned int Application::windowHeight = 480;
	SDL_Window* Application::window = NULL;
	SDL_Renderer* Application::renderer = NULL;

	Application::Application()
	{
		//
	}

	Application::~Application()
	{
		//
	}

	void Application::Initialize() {}
	void Application::LoadContent() {}
	void Application::UnloadContent() {}
	void Application::Update(long appTime) {}
	void Application::Draw(Graphics2D&g, long appTime) {}

	int Application::run(unsigned int width, unsigned int height, bool borderless)
	{
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

		if(borderless)
		{
			window = SDL_CreateWindow(NULL, 0, 0, 300, 300, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_SHOWN);
		}
		else
		{
			window = SDL_CreateWindow(NULL, 0, 0, 300, 300, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		return 0;
	}

	unsigned int Application::getWidth()
	{
		return windowWidth;
	}

	unsigned int Application::getHeight()
	{
		return windowHeight;
	}
}
