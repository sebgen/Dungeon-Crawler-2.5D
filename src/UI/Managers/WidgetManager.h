#ifndef RETRO3D_WIDGETMANAGER_H
#define RETRO3D_WIDGETMANAGER_H

#include "Misc/singleton.h"
#include "Object/objectptr.h"
#include "Window/window.h"
#include "UI/Widgets/widget.h"

namespace Retro3D
{
	//class Widget;

	class WidgetManager
	{
	private:
		ObjectPtr<Widget> mRootWidget;

		void renderWidgetRecursive(Widget* arg_widget, Window* arg_window);

		void tickWidgetRecursive(Widget* arg_widget, float arg_deltatime);

	public:
		WidgetManager();
		void AddWidget(Widget* arg_widget);

		void TickWidgets(float arg_deltatime);

		void RenderWidgets(Window* arg_window);

	};
}

#endif
