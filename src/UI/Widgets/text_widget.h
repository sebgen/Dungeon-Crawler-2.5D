#ifndef RETRO3D_TEXTWIDGET_H
#define RETRO3D_TEXTWIDGET_H

#include "visual_widget.h"
#include "UI/Visual/text_visual.h"

namespace Retro3D
{
	class TextWidget : public VisualWidget
	{
	protected:
		TextVisual mTextVisual;

	public:
		TextWidget();

		void SetText(const std::string &arg_string);

		TextStyle& GetTextStyle();

		virtual void CreateContent() override;

	};
}

#endif
