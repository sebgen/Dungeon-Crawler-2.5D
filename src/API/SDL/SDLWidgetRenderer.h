#ifndef RETRO3D_SFMLWIDGETRENDERER_H
#define RETRO3D_SFMLWIDGETRENDERER_H

#include "Window/window.h"
#include "UI/Interfaces/widget_renderer.h"
#include "Math/rectangle.h"
//#include "SFML/Graphics.hpp"

namespace Retro3D
{
	class SDLWindow;

	class SDLWidgetRenderer : public IWidgetRenderer
	{
	private:
		Window* mWindow = 0;

		void InitTransform(const Rectangle& arg_contentrect, const Rectangle& arg_visiblerect, SDL_Rect& out_rect);

	public:
		void RenderColour(ColourVisual* arg_visual, const WidgetRenderParams& arg_renderparams) override;
		void RenderImage(ImageVisual* arg_image, const WidgetRenderParams& arg_renderparams) override;
		void RenderText(TextVisual* arg_text, const WidgetRenderParams& arg_renderparams) override;
		
		void SetWindow(Window* arg_window) override;
	};
}

#endif
