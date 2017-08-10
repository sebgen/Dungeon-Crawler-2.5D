#include "image_widget.h"

namespace Retro3D
{
	ImageWidget::ImageWidget()
	{
		mColourVisual.Activate(false);
		mImageVisual.Activate(false);
		AddVisual(&mColourVisual);
		AddVisual(&mImageVisual);
	}

	void ImageWidget::SetImagePath(const std::string &arg_path)
	{
		mImageVisual.SetImagePath(arg_path);
		mImageVisual.Activate(arg_path != "");
	}

	void ImageWidget::SetColour(Colour arg_colour)
	{
		mColourVisual.SetColour(arg_colour);
		mColourVisual.Activate(arg_colour.IsVisible());
	}

	void ImageWidget::CreateContent()
	{

	}
}
