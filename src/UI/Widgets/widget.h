#ifndef RETRO3D_WIDGET_H
#define RETRO3D_WIDGET_H

#include "UI/Core/widgettransform.h"
#include <vector>
#include "Math/rectangle.h"
#include "Object/object.h"
#include "Object/objectptr.h"
#include "UI/Visual/visual.h"

namespace Retro3D
{
	class IWidgetRenderer;

	class Widget : public Object
	{
		friend class WidgetManager;

	protected:
		/**
		* Local transform of the Widget.
		*/
		WidgetTransform mTransform;

		/**
		* Cached absolute transform of the Widget.
		* If mTransformIsDirty == true, this needs to be recalculated.
		*/
		WidgetTransform mAbsoluteTransform;

		bool mTransformIsDirty;

		std::vector<ObjectPtr<Widget>> mChildWidgets;
		ObjectPtr<Widget> mParentWidget;

		std::vector<Visual*> mVisuals;


	public:
		Widget();

		virtual void CreateContent();

		/**
		* Called once, when the Widget has been created and is initialised.
		*/
		virtual void OnInitialise();

		/**
		* Called every frame.
		*/
		virtual void OnTick(float arg_deltatime);


		//virtual void OnInput(InputEvent arg_event);


		/**
		* Adds a pointer to a visual to be rendered.
		* Usually you want to call this from Widget::CreateContent()
		*/
		void AddVisual(Visual* arg_visual);


		/**
		* Marks the absolute transform as dirty.
		* This is called when doing transformations on the widget.
		*/
		void SetTransformDirty();

		void AddChildWidget(Widget* arg_widget);

		bool RemoveChildWidget(Widget* arg_widget);

		/***/
		/***** Modifiers ******/

		void SetPosition(glm::vec2 arg_pos);
		void SetSize(glm::vec2 arg_size);
		void SetPivot(glm::vec2 arg_pivot);

		inline void SetPosition(const float& x, const float& y) { SetPosition(glm::vec2(x, y)); }
		inline void SetSize(const float& w, const float& h) { SetSize(glm::vec2(w, h)); }
		inline void SetPivot(const float& x, const float& y) { SetPivot(glm::vec2(x, y)); }

		void SetVerticalPositioning(WidgetPositioningMode arg_mode);
		void SetHorizontalPositioning(WidgetPositioningMode arg_mode);
		void SetVerticalScaling(WidgetScalingMode arg_mode);
		void SetHorizontalScaling(WidgetScalingMode arg_mode);


		/***/
		/***** Accessors ******/

		const glm::vec2& GetPosition() const { return mTransform.mPosition; }
		const glm::vec2& GetSize() const { return mTransform.mSize; };
		const glm::vec2& GetPivot() const { return mTransform.mPivot; };

		const WidgetPositioningMode& GetVerticalPositioning() const { return mTransform.mVerticalPositioning; };
		const WidgetPositioningMode& GetHorizontalPositioning() const { return mTransform.mHorizontalPositioning; };
		const WidgetScalingMode& GetVerticalScaling() const { return mTransform.mVerticalScaling; };
		const WidgetScalingMode& GetHorizontalScaling() const { return mTransform.mHorizontalScaling; };

		const WidgetTransform& GetCachedAbsoluteTransform() const { return mAbsoluteTransform; };
		const WidgetTransform& GetAbsoluteTransform();

		const size_t GetNumChildWidgets() const;
		ObjectPtr<Widget> GetChildWidgetAt(const size_t& arg_index) const;

	};
}

#endif
