#include "map_editor_view.h"

#include <sdl2/SDL.h>
#include <sdl2/SDL_image.h>

#include "Engine/game_engine.h"
#include "World/level.h"
#include "Actor/player_controller.h"
#include "Actor/player.h"

namespace Retro3D
{
	MapEditorView::MapEditorView(NativeUI::Control* arg_parent)
		: NativeUI::UserControl(arg_parent)
	{
		mSDLWindow = SDL_CreateWindowFrom(mHwnd);
		mSDLRenderer = SDL_CreateRenderer(mSDLWindow, -1, SDL_RENDERER_ACCELERATED);
	}

	void MapEditorView::OnPaint()
	{
		SDL_SetRenderDrawColor(mSDLRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(mSDLRenderer);
		
		Retro3D::Level* level = GGameEngine->GetCurrentLevel();

		const bool drawCeiling = false; // TODO: make setting
		const bool drawFloor = true; // TODO: make setting

		const int dimX = level->GetDimensionX();
		const int dimY = level->GetDimensionY();

		// draw walls/floor/ceiling
		for (int x = 0; x < dimX; x++)
		{
			for (int y = 0; y < dimY; y++)
			{
				const int floorCell = level->GetFloorMapCell(x, y);
				const int ceilingCell = level->GetCeilingMapCell(x, y);
				const int wallCell = level->GetWallMapCell(x, y);
				const int textureMapIndex = wallCell != 0 ? wallCell : (drawCeiling ? ceilingCell : floorCell);

				SDL_Texture* texture = nullptr;
				auto textureMapIter = mTextureMap.find(textureMapIndex);
				if (textureMapIter != mTextureMap.end())
				{
					texture = textureMapIter->second;
				}
				else // create texture and cache it
				{
					auto textureMap = level->GetTextureMap();
					const std::string textureName = textureMap[textureMapIndex];
					std::string fullPath = std::string("resources//textures//") + textureName;
					SDL_Surface* surface = IMG_Load(fullPath.c_str());
					texture = SDL_CreateTextureFromSurface(mSDLRenderer, surface);
					SDL_FreeSurface(surface);
					mTextureMap[textureMapIndex] = texture;
				}

				if (texture != nullptr)
				{
					SDL_Rect rect;
					rect.x = x * mCellSize;
					rect.y = y * mCellSize;
					rect.w = mCellSize;
					rect.h = mCellSize;

					SDL_RenderCopy(mSDLRenderer, texture, NULL, &rect);
				}

				// if wall: draw a cross
				if (wallCell != 0)
				{
					SDL_RenderDrawLine(mSDLRenderer, x * mCellSize, y * mCellSize, (x+1)*mCellSize, (y+1)*mCellSize);
					SDL_RenderDrawLine(mSDLRenderer, x * mCellSize, (y + 1) * mCellSize, (x + 1)*mCellSize, y*mCellSize);
				}
			}
		}

		SDL_SetRenderDrawColor(mSDLRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

		// Draw grid
		for (int i = 0; i < dimX && i < dimY; i++)
		{
			if (i < dimX)
			{
				SDL_RenderDrawLine(mSDLRenderer, i * mCellSize, 0, i * mCellSize, dimY * mCellSize);
			}
			if(i < dimY)
			{
				SDL_RenderDrawLine(mSDLRenderer, 0, i * mCellSize, dimX * mCellSize, i * mCellSize);
			}
		}

		const glm::vec3 playerPos = GGameEngine->GetPlayerController()->GetPlayer()->GetTransform().GetPosition();
		const int playerX = playerPos.x * mCellSize;
		const int playerY = playerPos.y * mCellSize;
		const int crossLX = playerX - mCellSize * 0.5f;
		const int crossRX = playerX + mCellSize * 0.5f;
		const int crossTY = playerY - mCellSize * 0.5f;
		const int crossBY = playerY + mCellSize * 0.5f;

		SDL_RenderDrawLine(mSDLRenderer, crossLX, playerY, crossRX, playerY);
		SDL_RenderDrawLine(mSDLRenderer, playerX, crossTY, playerX, crossBY);
		SDL_RenderDrawLine(mSDLRenderer, crossLX, crossTY, crossRX, crossBY);
		SDL_RenderDrawLine(mSDLRenderer, crossLX, crossBY, crossRX, crossTY);

		SDL_RenderPresent(mSDLRenderer);
	}

}
