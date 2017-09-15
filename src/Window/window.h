#ifndef RETRO3D_WINDOW_H
#define RETRO3D_WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

namespace Retro3D
{
	class Window
	{
	private:
		SDL_Window* mSDLWindow;
		SDL_Renderer* mSDLRenderer;

	public:
		Window();
		~Window();

		void PrepareRender();
		void Render();

		inline SDL_Window* GetSDLWindow()
		{
			return mSDLWindow;
		}

		inline SDL_Renderer* GetSDLRenderer()
		{
			return mSDLRenderer;
		}

		void GetWindowSize(int& out_width, int& out_height);
	};
}

#endif
