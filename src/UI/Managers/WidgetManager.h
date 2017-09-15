#ifndef RETRO3D_WIDGETMANAGER_H
#define RETRO3D_WIDGETMANAGER_H

#include "Misc/singleton.h"
#include "Object/objectptr.h"
#include "Window/window.h"
#include "UI/Widgets/widget.h"
#include "Engine/input_listener.h"

namespace Retro3D
{
	//class Widget;

	class WidgetManager : public IInputListener
	{
	private:
		ObjectPtr<Widget> mRootWidget;

		void renderWidgetRecursive(Widget* arg_widget, Window* arg_window);

		void tickWidgetRecursive(Widget* arg_widget, float arg_deltatime);

		void mouseEventRecursive(Widget* arg_widget, const glm::vec2& arg_mousepos, int arg_mouseevent, MouseButtonID arg_button);

	public:
		WidgetManager();
		void AddWidget(Widget* arg_widget);

		void TickWidgets(float arg_deltatime);

		void RenderWidgets(Window* arg_window);

		virtual void OnKeyDown(const char* arg_key) override;
		virtual void OnKeyUp(const char* arg_key) override;
		virtual void OnMouseButtonDown(MouseButtonID arg_button) override;
		virtual void OnMouseButtonUp(MouseButtonID arg_button) override;
	};
}

#endif
