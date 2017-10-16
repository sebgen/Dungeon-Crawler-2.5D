#ifndef RETRO3D_WINDOW_H
#define RETRO3D_WINDOW_H

/*=============================================================================================
Game Window class.

The Game, with its scene and GUI, is rendered here.

==============================================================================================*/

#include "Graphics/render_target.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

namespace Retro3D
{
	class Window : public IRenderTargetWindow
	{
	private:
		SDL_Window* mSDLWindow;
		SDL_Renderer* mSDLRenderer;

	public:
		Window();
		~Window();

		/** Prepare the Window for rendering. Called by the engine. */
		virtual void PrepareRender() override;

		/** Updates the screen with rendered content. */
		virtual void Render() override;

		inline SDL_Window* GetSDLWindow() { return mSDLWindow; }

		virtual SDL_Renderer* GetSDLRenderer() override;

		/** Gets the size (in pixels) of the Window. */
		virtual void GetWindowSize(int& out_width, int& out_height) override;
	};
}

#endif
