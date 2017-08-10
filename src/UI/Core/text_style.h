#ifndef TEXT_STYLE_H
#define TEXT_STYLE_H

#include <string>
#include "colour.h"

namespace Retro3D
{
	class TextStyle
	{
	private:
		std::string mFontName;
		unsigned int mFontSize;
		Retro3D::Colour mColour;
		bool mWrapText;

	public:
		TextStyle();

		void SetFontName(const std::string& arg_fontname);
		void SetFontSize(unsigned int arg_fontsize);
		void SetColour(const Colour& arg_colour);
		void SetWrapText(bool arg_wwap);

		const std::string& GetFontName() const { return mFontName; };
		unsigned int GetFontSize() const { return mFontSize; };
		const Retro3D::Colour& GetColour() const { return mColour; };
		const bool GetWrapText() const { return mWrapText; }

	};
}

#endif
