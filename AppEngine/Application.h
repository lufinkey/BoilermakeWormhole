
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
	public:
		Application();
		virtual ~Application();

		virtual void Initialize();
		virtual void LoadContent();
		virtual void UnloadContent();
		virtual void Update(long appTime);
		virtual void Draw(Graphics2D&g, long appTime);

		static unsigned int getWidth();
		static unsigned int getHeight();
	};
}


