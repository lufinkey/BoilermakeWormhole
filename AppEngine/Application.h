
#include "Graphics/Graphics2D.h"

#pragma once

namespace AppEngine
{
	class Application
	{
		friend class BufferedImage;
	private:
		static SDL_Window* window;
		static SDL_Renderer* renderer;

		static unsigned int windowWidth;
		static unsigned int windowHeight;

		static bool appRunning;
		static bool appClosing;

		static Application* appInstance;

		static Graphics2D* graphics;

		static long appTime;
		static long sleepTime;

		static bool KeyState[526];
		static bool currentKeyState[526];
		static bool prevKeyState[526];
		static int lastKey;

		void updateEvents();

		static void keyPressed(int keycode);
		static void keyReleased(int keycode);

	public:
		Application();
		virtual ~Application();

		virtual void Initialize();
		virtual void LoadContent();
		virtual void UnloadContent();
		virtual void Update(long appTime);
		virtual void Draw(Graphics2D&g, long appTime);

		int run(unsigned int width, unsigned int height, bool borderless = false);

		static unsigned int getWidth();
		static unsigned int getHeight();
	};
}


