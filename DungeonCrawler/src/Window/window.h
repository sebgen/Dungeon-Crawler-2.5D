#ifndef RETRO3D_WINDOW_H
#define RETRO3D_WINDOW_H

/*=============================================================================================
Game Window class.

The Game, with its scene and GUI, is rendered here.

==============================================================================================*/

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

		/** Prepare the Window for rendering. Called by the engine. */
		void PrepareRender();

		/** Updates the screen with rendered content. */
		void Render();

		inline SDL_Window* GetSDLWindow() { return mSDLWindow; }

		inline SDL_Renderer* GetSDLRenderer() { return mSDLRenderer;  }

		/** Gets the size (in pixels) of the Window. */
		void GetWindowSize(int& out_width, int& out_height);
	};
}

#endif
