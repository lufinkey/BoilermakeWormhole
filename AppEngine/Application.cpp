
#include "Application.h"
#include "Output\Console.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Input\Keys.h"
#include <time.h>

namespace AppEngine
{
	SDL_Window* Application::window = NULL;
	SDL_Renderer* Application::renderer = NULL;

	unsigned int Application::windowWidth = 640;
	unsigned int Application::windowHeight = 480;

	bool Application::appRunning = false;
	bool Application::appClosing = false;

	Application* Application::appInstance = NULL;

	Graphics2D* Application::graphics = NULL;

	bool Application::KeyState[526];
	bool Application::currentKeyState[526];
	bool Application::prevKeyState[526];
	int Application::lastKey = 0;

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
		appRunning = true;

		srand((unsigned)time(NULL));

		if(!SDL_WasInit(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER))
		{
			if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) < 0)
			//if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
			{
				Console::WriteLine("failed to initialize SDL library");
				appRunning = false;
				return 1;
			}
		}

		if(!TTF_WasInit())
		{
			if(TTF_Init() < 0)
			{
				Console::WriteLine("failed to initalize SDL_ttf library");
				appRunning = false;
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

		if(window == NULL)
		{
			Console::WriteLine("failed to create SDL_Window");
			appRunning = false;
			return 1;
		}

		windowWidth = width;
		windowHeight = height;

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if(renderer == NULL)
		{
			Console::WriteLine("failed to create SDL_Renderer from SDL_Window");
			appRunning = false;
			return 1;
		}

		appInstance = this;

		this->Initialize();

		graphics = new Graphics2D();
		graphics->renderer = renderer;

		this->LoadContent();

		while(appRunning && !appClosing)
		{
			//
		}

		return 0;
	}

	void Application::updateEvents()
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
				this->UnloadContent();
				graphics->renderer = NULL;
				SDL_DestroyRenderer(renderer);
				renderer = NULL;
				SDL_DestroyWindow(window);
				window = NULL;
				appClosing = true;
				break;
				
				case SDL_KEYDOWN:
				keyPressed(Keys::SDLK_to_KeyCode(event.key.keysym.sym));
				break;
				
				case SDL_KEYUP:
				keyReleased(Keys::SDLK_to_KeyCode(event.key.keysym.sym));
				break;
			}
		}
		SDL_JoystickUpdate();
	}

	void Application::keyPressed(int keycode)
	{
		if(keycode!=0)
		{
			KeyState[keycode] = true;
			lastKey = keycode;
		}
	}
	
	void Application::keyReleased(int keycode)
	{
		if(keycode!=0)
		{
			KeyState[keycode] = false;
		}
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
