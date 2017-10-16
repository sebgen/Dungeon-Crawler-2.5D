#include "window.h"
#include <iostream>

namespace Retro3D
{
	Window::Window()
	{
		mSDLWindow = SDL_CreateWindow("2.5D test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
		mSDLRenderer = SDL_CreateRenderer(mSDLWindow, -1, SDL_RENDERER_ACCELERATED);

		/*** SDL initialisation ***/
		SDL_RendererInfo info;
		SDL_GetRendererInfo(mSDLRenderer, &info);
		std::cout << "Renderer: " << info.name << std::endl;
		std::cout << "Texture formats: " << std::endl;
		for (Uint32 i = 0; i < info.num_texture_formats; i++)
		{
			std::cout << SDL_GetPixelFormatName(info.texture_formats[i]) << std::endl;
		}
	}

	Window::~Window()
	{
		SDL_DestroyRenderer(mSDLRenderer);
		SDL_DestroyWindow(mSDLWindow);
	}

	void Window::PrepareRender()
	{
		SDL_SetRenderDrawColor(mSDLRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(mSDLRenderer);
	}

	void Window::Render()
	{
		SDL_RenderPresent(mSDLRenderer);
	}

	SDL_Renderer* Window::GetSDLRenderer() 
	{
		return mSDLRenderer; 
	}

	void Window::GetWindowSize(int& out_width, int& out_height)
	{
		SDL_GetWindowSize(GetSDLWindow(), &out_width, &out_height);
	}

}
