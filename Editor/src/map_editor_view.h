#ifndef RETRO3D_MAPEDITORVIEW_H
#define RETRO3D_MAPEDITORVIEW_H

#include "user_control.h"

struct SDL_Window; // fwd. decl.
struct SDL_Renderer;
struct SDL_Texture;

namespace Retro3D
{
	class MapEditorView : public NativeUI::UserControl
	{
	private:
		SDL_Renderer* mSDLRenderer;
		SDL_Window* mSDLWindow;

		const int mCellSize = 35;
		std::unordered_map<char, SDL_Texture*> mTextureMap;

	public:
		MapEditorView(NativeUI::Control* arg_parent);

		virtual void OnPaint() override;
	};
}

#endif
