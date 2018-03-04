#ifndef RETRO3D_PLAYERCONTROLLER_H
#define RETRO3D_PLAYERCONTROLLER_H

#include "glm/glm.hpp"

namespace Retro3D
{
	class Player;

	class PlayerController
	{
	private:
		bool IsValidMoveLocation(const glm::vec3 arg_loc);

		glm::vec3 mRequestedVelocity;
		glm::vec3 mRequestedRotation;

	protected:
		Player* mPlayer = nullptr;

		void ConsumeInput();

	public:
		void SetPlayer(Player* arg_player);

		inline Player* GetPlayer() { return mPlayer; }

		virtual void OnStart();
		virtual void OnTick(float arg_deltatime);

	};
}

#endif
