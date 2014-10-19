
#include "Graphics/Graphics2D.h"
#include "Input/DragDropTarget.h"

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
		static Color bgColor;

		static bool appRunning;
		static bool appClosing;

		static Application* appInstance;

		static Graphics2D* graphics;
		static DragDropTarget* dropTarget;

		static long appTime;
		static long sleepTime;

		static const int totalKeys = 526;
		static bool KeyState[526];
		static bool currentKeyState[526];
		static bool prevKeyState[526];
		static int lastKey;
		static int currentLastKey;

		void updateEvents();

		static void keyPressed(int keycode);
		static void keyReleased(int keycode);
		static void updateKeys(bool*keys1, bool*keys2);

	public:
		Application();
		virtual ~Application();

		virtual void Initialize();
		virtual void LoadContent();
		virtual void UnloadContent();
		virtual void Update(long appTime);
		virtual void Draw(Graphics2D&g, long appTime);

		virtual DWORD onDropEnter(IDataObject* dataObj, Vector2<long> point);
		virtual void onDropLeave();
		virtual DWORD onDropDragOver(Vector2<long> point);
		virtual DWORD onDrop(IDataObject* dataObj, Vector2<long> point);

		int run(unsigned int width, unsigned int height, bool borderless = false);

		static unsigned int getWidth();
		static unsigned int getHeight();
	};
}


