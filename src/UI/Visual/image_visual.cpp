#include "image_visual.h"

#include "UI/Interfaces/widget_renderer.h"

namespace Retro3D
{
	void ImageVisual::RenderVisual(IWidgetRenderer *arg_renderer, const WidgetRenderParams& arg_renderparams)
	{
		arg_renderer->RenderImage(this, arg_renderparams);
	}

	void ImageVisual::SetImagePath(std::string arg_img)
	{
		mImagePath = arg_img;
	}
}