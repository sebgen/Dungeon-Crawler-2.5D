#ifndef RETRO3D_IMAGEWIDGET_H
#define RETRO3D_IMAGEWIDGET_H

#include "visual_widget.h"
#include "UI/Visual/image_visual.h"
#include "UI/Visual/colour_visual.h"

namespace Retro3D
{
	class ImageWidget : public VisualWidget
	{
	protected:
		ColourVisual mColourVisual;
		ImageVisual mImageVisual;

	public:
		ImageWidget();

		void SetImagePath(const std::string &arg_path);
		void SetColour(Colour arg_colour);

		virtual void CreateContent() override;

	};
}

#endif
