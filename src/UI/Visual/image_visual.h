#ifndef RETRO3D_UI_IMAGE_VISUAL_H
#define RETRO3D_UI_IMAGE_VISUAL_H

#include "UI/Visual/visual.h"
#include <string>
#include "Resource/texture_res.h"
#include "Resource/res_ptr.h"

namespace Retro3D
{
	class ImageVisual : public Visual
	{
	private:
		std::string mImagePath;
		ResPtr<TextureRes> mImageRes;
		SDL_Texture* mSDLTexture = nullptr;

	public:
		
		ImageVisual();
		~ImageVisual();

		void RenderVisual(IWidgetRenderer *arg_renderer, const WidgetRenderParams& arg_renderparams);

		void SetImagePath(std::string arg_img);

		std::string GetImagePath() { return mImagePath; }

		inline SDL_Texture* GetSDLTexture() { return mSDLTexture; }
	};
}

#endif
