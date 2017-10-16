#ifndef I_RETRO3D_RENDERTARGETWINDOW_H
#define I_RETRO3D_RENDERTARGETWINDOW_H

struct SDL_Renderer; // fwd. decl.

namespace Retro3D
{
	class IRenderTargetWindow
	{
	public:
		virtual void PrepareRender() = 0;
		virtual void Render() = 0;

		virtual SDL_Renderer* GetSDLRenderer() = 0;

		virtual void GetWindowSize(int& out_width, int& out_height) = 0;
	};
}

#endif
