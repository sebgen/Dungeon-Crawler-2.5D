#include "font_res.h"

#include "Misc/debug.h"
#include "Engine/game_engine.h"

namespace Retro3D
{
	bool FontRes::LoadResource(const std::string& arg_path)
	{
		mFont = TTF_OpenFont(arg_path.c_str(), 20); // TODO: font size (hard coded to be 20)

		return (mFont != nullptr);
	}

	FontRes::~FontRes()
	{
		if (mFont != nullptr)
		{
			TTF_CloseFont(mFont);
		}
	}
}
