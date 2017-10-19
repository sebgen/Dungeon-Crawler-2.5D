#ifndef RETRO3D_EDITOR_H
#define RETRO3D_EDITOR_H

#include "editor_window.h"

namespace Retro3D
{
	class Editor
	{
	private:
		Editor();
		EditorWindow* mEditorWinndow = nullptr;

	public:
		static Editor* CreateEditor();
		
		void RunEditor();
	};

	extern Editor* GEditor;
}

#endif
