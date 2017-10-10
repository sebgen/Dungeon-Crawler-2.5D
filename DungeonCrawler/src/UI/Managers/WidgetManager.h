#ifndef RETRO3D_WIDGETMANAGER_H
#define RETRO3D_WIDGETMANAGER_H

/*=============================================================================================
Widget Manager

Owns and updates all Widgets.
Deals with Widget ticking, input handling and rendering of Widgets.

==============================================================================================*/

#include "Misc/singleton.h"
#include "Object/objectptr.h"
#include "Window/window.h"
#include "UI/Widgets/widget.h"
#include "Engine/input_listener.h"
#include <functional>

namespace Retro3D
{
	//class Widget;

	class WidgetManager : public IInputListener
	{
	private:
		ObjectPtr<Widget> mRootWidget;

		void renderWidgetRecursive(Widget* arg_widget, Window* arg_window);

		/**
		* Iterates through widgets and child widgets, starting from arg_widget.
		* Calls arg_function on each widgets, and continues with children if it returned true.
		* @param  arg_widget    Widget to start recursive iteration from.
		* @param  arg_function  Function to be called on each widget. If it returns true, arg_widget's children will also be evaluated.
		*/
		void iterateWidgetsRecursive(Widget* arg_widget, std::function<bool(Widget*)> arg_function);

		std::unordered_map<int, std::vector<WeakObjectPtr<Widget>>> mMouseButtonDownWidgets;
		std::vector<WeakObjectPtr<Widget>> mHoveredWidgets;

	public:
		WidgetManager();

		/** Adds a Widget to the widget tree. */
		void AddWidget(Widget* arg_widget);

		/** Updates all Widgets. */
		void TickWidgets(float arg_deltatime);

		/** Renders all Widgets. */
		void RenderWidgets(Window* arg_window);

		// IInputListener callbacks
		virtual void OnKeyDown(const char* arg_key) override;
		virtual void OnKeyUp(const char* arg_key) override;
		virtual void OnMouseButtonDown(MouseButtonID arg_button) override;
		virtual void OnMouseButtonUp(MouseButtonID arg_button) override;
		virtual void OnMouseMotion(const glm::vec2& arg_motion) override;

		Widget* CurrentWidget; // UGLY!! TODO
	};
}

#endif
