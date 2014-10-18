
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


