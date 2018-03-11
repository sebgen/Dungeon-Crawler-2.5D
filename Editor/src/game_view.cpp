#include "game_view.h"
#include <sdl2/SDL.h>
#include <sdl2/SDL_image.h>

namespace Retro3D
{
	GameView::GameView(Control* arg_parent)
		: UserControl(arg_parent)
	{
		mSDLWindow = SDL_CreateWindowFrom(mHwnd);
		mSDLRenderer = SDL_CreateRenderer(mSDLWindow, -1, SDL_RENDERER_ACCELERATED);
	}

	void GameView::OnPaint()
	{
		SDL_RenderPresent(mSDLRenderer);
	}

	void GameView::PrepareRender()
	{
		SDL_SetRenderDrawColor(mSDLRenderer, 255	, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(mSDLRenderer);
	}

	void GameView::Render()
	{
		SDL_RenderPresent(mSDLRenderer);
	}

	SDL_Renderer* GameView::GetSDLRenderer()
	{
		return mSDLRenderer;
	}

	void GameView::GetRenderContextSize(int& out_width, int& out_height)
	{
		SDL_GetWindowSize(mSDLWindow, &out_width, &out_height);
	}

	void GameView::GetWindowSize(int& out_width, int& out_height)
	{
		return GetRenderContextSize(out_width, out_height);
	}

	void* GameView::GetOSWindowHandle()
	{
		return mHwnd;
	}

	bool GameView::HasFocus()
	{
		return GetActiveWindow() == mHwnd;
	}

	IWindow* GameView::GetWindow()
	{
		return this;
	}
}