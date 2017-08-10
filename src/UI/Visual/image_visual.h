#ifndef RETRO3D_UI_IMAGE_VISUAL_H
#define RETRO3D_UI_IMAGE_VISUAL_H

#include "UI/Visual/visual.h"
#include <string>

namespace Retro3D
{
	class ImageVisual : public Visual
	{
	private:
		std::string mImagePath;
	public:
		void RenderVisual(IWidgetRenderer *arg_renderer, const WidgetRenderParams& arg_renderparams);

		void SetImagePath(std::string arg_img);

		std::string GetImagePath() { return mImagePath; }
	};
}

#endif
