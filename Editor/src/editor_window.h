#ifndef RETRO3D_EDITORWINDOW_H
#define RETRO3D_EDITORWINDOW_H

#include "window.h"
#include "game_view.h"
#include "map_editor_view.h"

namespace Retro3D
{
	class EditorWindow : public NativeUI::Window
	{
	private:
		GameView* mGameView;
		MapEditorView* mMapEditorView;

	public:
		EditorWindow();

		inline GameView* GetGameView() { return mGameView; }
	};
}

#endif
