#include "WidgetManager.h"

#include "Engine/game_engine.h"
#include "UI/Interfaces/widget_renderer.h"
#include "Engine/input_manager.h"

namespace Retro3D
{
	WidgetManager::WidgetManager()
	{
		mRootWidget = new Widget();
		mRootWidget->SetSize(1.0f, 1.0f);
	}

	void WidgetManager::AddWidget(Widget* arg_widget)
	{
		mRootWidget->AddChildWidget(arg_widget);
		if (!arg_widget->mHasCreatedContent)
		{
			arg_widget->CreateContent();
		}
	}

	void WidgetManager::TickWidgets(float arg_deltatime)
	{
		std::function<bool(Widget*)> func = [&](Widget* arg_widget) -> bool
		{
			CurrentWidget = arg_widget;
			arg_widget->OnTick(arg_deltatime);
			return true;
		};

		iterateWidgetsRecursive(mRootWidget.Get(), func);
	}

	void WidgetManager::RenderWidgets(Window* arg_window)
	{
		IWidgetRenderer* widgetRenderer = GGameEngine->GetWidgetRenderer();
		widgetRenderer->SetWindow(arg_window);
		for (size_t i = 0; i < mRootWidget->GetNumChildWidgets(); i++)
		{
			ObjectPtr<Widget> currentWidget = mRootWidget->GetChildWidgetAt(i);
			renderWidgetRecursive(currentWidget.Get(), arg_window);
		}
		
	}

	void WidgetManager::renderWidgetRecursive(Widget* arg_widget, Window* arg_window)
	{
		__Assert(arg_widget->mParentWidget != nullptr);
		__Assert(arg_window != nullptr);

		IWidgetRenderer* widgetRenderer = GGameEngine->GetWidgetRenderer();
		const WidgetTransform& widgetTrans = arg_widget->GetAbsoluteTransform();
		const WidgetTransform& parentTrans = arg_widget->mParentWidget->GetAbsoluteTransform();

		// TODO: USE INT CALCULATION
		// Calculate content rect (rect to render widget in) and visible rect (usually the same, unless parent widget is smaller)
		const glm::vec2 contentXYBounds = widgetTrans.mPosition + widgetTrans.mSize;
		const glm::vec2 parentXYBounds = parentTrans.mPosition + parentTrans.mSize;
		const float visiblePosX = std::fminf(std::fmaxf(widgetTrans.mPosition.x, parentTrans.mPosition.x), parentXYBounds.x);
		const float visiblePosY = std::fminf(std::fmaxf(widgetTrans.mPosition.y, parentTrans.mPosition.y), parentXYBounds.y);
		const float visibleSizeW = std::fminf(contentXYBounds.x, parentXYBounds.x) - visiblePosX;
		const float visibleSizeH = std::fminf(contentXYBounds.y, parentXYBounds.y) - visiblePosY;
		WidgetRenderParams renderParams;
		renderParams.mContentRect = Rectangle(widgetTrans.mPosition, widgetTrans.mSize);
		renderParams.mVisibleRect = Rectangle(glm::vec2(visiblePosX, visiblePosY), glm::vec2(visibleSizeW, visibleSizeH));
		
		for (ObjectPtrBase<Visual> visual : arg_widget->mVisuals)
		{
			if(visual->IsActivated())
				visual->RenderVisual(widgetRenderer, renderParams);
		}

		for (size_t i = 0; i < arg_widget->GetNumChildWidgets(); i++)
		{
			ObjectPtr<Widget> currentWidget = arg_widget->GetChildWidgetAt(i);
			renderWidgetRecursive(currentWidget.Get(), arg_window);
		}
	}

	void WidgetManager::OnKeyDown(const char* arg_key)
	{
		// TODO: forward to selected/highlighted widget
	}

	void WidgetManager::OnKeyUp(const char* arg_key)
	{
		// TODO: forward to selected/highlighted widget
	}

	void WidgetManager::OnMouseButtonDown(MouseButtonID arg_button)
	{
		int win_w;
		int win_h;
		GGameEngine->GetWindow()->GetWindowSize(win_w, win_h);

		glm::vec2 relMousePos = GGameEngine->GetInputManager()->GetMousePosition() / glm::vec2(win_w, win_h);

		std::function<bool(Widget*)> func = [&](Widget* arg_widget) -> bool
		{
			CurrentWidget = arg_widget;

			const glm::vec2 widgetPos = arg_widget->mAbsoluteTransform.mPosition;
			const glm::vec2 widgetRBPos = arg_widget->mAbsoluteTransform.mSize + widgetPos;

			if (relMousePos.x > widgetPos.x && relMousePos.x < widgetRBPos.x && relMousePos.y > widgetPos.y && relMousePos.y < widgetRBPos.y)
			{
				arg_widget->OnMouseButtonDown(arg_button);

				auto widgetArrayIter = mMouseButtonDownWidgets.find((int)arg_button);
				if (widgetArrayIter == mMouseButtonDownWidgets.end())
				{
					mMouseButtonDownWidgets.emplace((int)arg_button, std::vector<WeakObjectPtr<Widget>>());
					widgetArrayIter = mMouseButtonDownWidgets.find((int)arg_button);
				}
				widgetArrayIter->second.push_back(arg_widget);

				return true;
			}
			return false;
		};

		iterateWidgetsRecursive(mRootWidget.Get(), func);
	}

	void WidgetManager::OnMouseButtonUp(MouseButtonID arg_button)
	{
		auto widgetArrayIter = mMouseButtonDownWidgets.find((int)arg_button);
		if (widgetArrayIter != mMouseButtonDownWidgets.end())
		{
			for (ObjectPtrBase<Widget>& widget : widgetArrayIter->second)
			{
				widget->OnMouseButtonUp(arg_button);
			}
			widgetArrayIter->second.clear();
		}
	}

	void WidgetManager::OnMouseMotion(const glm::vec2& arg_motion)
	{
		int win_w;
		int win_h;
		GGameEngine->GetWindow()->GetWindowSize(win_w, win_h);

		glm::vec2 relMousePos = GGameEngine->GetInputManager()->GetMousePosition() / glm::vec2(win_w, win_h);

		std::vector<WeakObjectPtr<Widget>> widgetsNoLongerHovered;

		std::function<bool(Widget*)> funcMouseMotion = [&](Widget* arg_widget) -> bool
		{
			CurrentWidget = arg_widget;

			const glm::vec2 widgetPos = arg_widget->mAbsoluteTransform.mPosition;
			const glm::vec2 widgetRBPos = arg_widget->mAbsoluteTransform.mSize + widgetPos;

			if (relMousePos.x > widgetPos.x && relMousePos.x < widgetRBPos.x && relMousePos.y > widgetPos.y && relMousePos.y < widgetRBPos.y)
			{
				if (!arg_widget->mIsHovered)
				{
					arg_widget->OnMouseEnter();
					arg_widget->mIsHovered = true;
				}

				arg_widget->OnMouseMotion(arg_motion);

				return true;
			}
			else
			{
				// Tell widget and children that we are no longer hovering
				if (arg_widget->mIsHovered)
				{
					widgetsNoLongerHovered.push_back(arg_widget);
				}
			}
			return false;
		};

		iterateWidgetsRecursive(mRootWidget.Get(), funcMouseMotion);

		// Iterate through all widgets that no longer are hovered, and call OnMouseLeave()
		std::function<bool(Widget*)> funcOnMouseLeave = [&](Widget* arg_widget) -> bool
		{
			if (arg_widget->mIsHovered)
			{
				CurrentWidget = arg_widget;
				arg_widget->OnMouseLeave();
				arg_widget->mIsHovered = false;

				return true; // continue with children
			}
			
			return false;
		};

		for (auto& widget : widgetsNoLongerHovered)
		{
			iterateWidgetsRecursive(widget.Get(), funcOnMouseLeave);
		}

	}

	void WidgetManager::iterateWidgetsRecursive(Widget* arg_widget, std::function<bool(Widget*)> arg_function)
	{
		bool continueWithChildren = arg_function(arg_widget);
		if (continueWithChildren)
		{
			for(ObjectPtrBase<Widget>& child : arg_widget->mChildWidgets)
				iterateWidgetsRecursive(child.Get(), arg_function);
		}
	}
}