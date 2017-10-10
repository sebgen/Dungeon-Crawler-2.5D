#include "image_visual.h"

#include "UI/Interfaces/widget_renderer.h"
#include "Engine/game_engine.h"
#include "Window/window.h"
#include "Resource/resource_manager.h"

namespace Retro3D
{
	
	ImageVisual::ImageVisual()
	{

	}

	ImageVisual::~ImageVisual()
	{
		if (mSDLTexture != nullptr)
		{
			SDL_DestroyTexture(mSDLTexture);
		}
	}

	void ImageVisual::RenderVisual(IWidgetRenderer *arg_renderer, const WidgetRenderParams& arg_renderparams)
	{
		arg_renderer->RenderImage(this, arg_renderparams);
	}

	void ImageVisual::SetImagePath(std::string arg_img)
	{
		mImagePath = arg_img;
		// TODO: don't do that here
		mImageRes = GGameEngine->GetResourceManager()->LoadResource<TextureRes>(mImagePath);
		if (mImageRes.IsValid())
		{
			if (mSDLTexture != nullptr)
			{
				SDL_DestroyTexture(mSDLTexture);
			}
			mSDLTexture = SDL_CreateTextureFromSurface(GGameEngine->GetWindow()->GetSDLRenderer(), mImageRes->GetSDLSurface());
		}
	}
}
