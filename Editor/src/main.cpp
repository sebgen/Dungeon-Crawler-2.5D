#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

#define SDL_MAIN_HANDLED

#include "editor.h"

using namespace Retro3D;

int main()
{
	Editor* editor = Editor::CreateEditor();
	editor->RunEditor();

	return 0;
}