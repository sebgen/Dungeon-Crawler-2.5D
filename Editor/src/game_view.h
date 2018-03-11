#ifndef RETRO3DGAME_VIEW_H
#define RETRO3DGAME_VIEW_H

#include "API/SDL/sdl_render_target.h"
#include "user_control.h"

struct SDL_Window; // fwd. decl

namespace Retro3D
{
	class GameView : public NativeUI::UserControl, public ISDLRenderTarget, public IWindow
	{
	private:
		SDL_Renderer* mSDLRenderer;
		SDL_Window* mSDLWindow;

	public:
		GameView(Control* arg_parent);

		virtual void OnPaint() override;

		virtual void PrepareRender() override;
		virtual void Render() override;
		virtual SDL_Renderer* GetSDLRenderer() override;

		virtual void GetRenderContextSize(int& out_width, int& out_height) override;
		virtual void GetWindowSize(int& out_width, int& out_height) override;
		virtual void* GetOSWindowHandle() override;
		virtual bool HasFocus() = 0;
		virtual IWindow* GetWindow() override;
	};
}

#endif
