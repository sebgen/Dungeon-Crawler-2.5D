#include "player_controller.h"

#include "Engine/input_manager.h"
#include "Engine/game_engine.h"
#include "player.h"
#include "World/level.h"

namespace Retro3D
{
	void PlayerController::SetPlayer(Player* arg_player)
	{
		mPlayer = arg_player;
	}

	void PlayerController::OnStart()
	{

	}

	void PlayerController::OnTick(float arg_deltatime)
	{
		if (mPlayer)
		{
			const float deltaSeconds = arg_deltatime;

			ConsumeInput();

			glm::vec3 playerPos = mPlayer->GetTransform().GetPosition();
			glm::mat4 playerRot = mPlayer->GetTransform().GetRotation();

			const float movementSpeed = deltaSeconds * 2.5f; // TODO

			const bool initialOverlap = !IsValidMoveLocation(playerPos);

			glm::vec3 moveDist = mRequestedVelocity * movementSpeed;

			if (glm::length(moveDist) > 0.0f)
			{
				const glm::vec3 moveDir = glm::normalize(moveDist);
				moveDist = moveDir * movementSpeed;

				if (!initialOverlap && !IsValidMoveLocation(playerPos + moveDist))
				{
					const bool xMoveValid = IsValidMoveLocation(playerPos + glm::vec3(moveDist.x, 0.0f, 0.0f));
					const bool yMoveValid = IsValidMoveLocation(playerPos + glm::vec3(0.0f, moveDist.y, 0.0f));

					if (xMoveValid)
					{
						moveDist = glm::vec3(moveDist.x, 0.0f, 0.0f);
					}
					else if (yMoveValid)
					{
						moveDist = glm::vec3(0.0f, moveDist.y, 0.0f);
					}
					else
					{
						moveDist = glm::vec3(0.0f, 0.0f, 0.0f);
					}
				}

				const glm::vec3 newPos = playerPos + moveDist;

				mPlayer->GetTransform().SetPosition(newPos);
			}

			if (glm::length(mRequestedRotation) > 0.0f)
			{
				glm::mat4 rotMat = glm::rotate(movementSpeed, mRequestedRotation);;
				mPlayer->GetTransform().SetRotation(playerRot * rotMat);
			}
		}
	}

	bool PlayerController::IsValidMoveLocation(const glm::vec3 arg_loc)
	{
		const float DESIRED_WALL_DISTANCE = 0.15f;
		Level* level = GGameEngine->GetCurrentLevel();

		const int intX = (int)arg_loc.x;
		const int intY = (int)arg_loc.y;
		const float fractX = arg_loc.x - intX;
		const float fractY = arg_loc.y - intY;

		const bool crossRight = fractX + DESIRED_WALL_DISTANCE > 1.0f;
		const bool crossLeft = fractX - DESIRED_WALL_DISTANCE < 0.0f;
		const bool crossFwd = fractY + DESIRED_WALL_DISTANCE > 1.0f;
		const bool crossBack = fractY - DESIRED_WALL_DISTANCE < 0.0f;

		if (!level->IsWalkableFloor(intX, intY)
			|| crossRight && !level->IsWalkableFloor(intX + 1, intY)
			|| crossLeft && !level->IsWalkableFloor(intX - 1, intY)
			|| crossFwd && !level->IsWalkableFloor(intX, intY + 1)
			|| crossBack && !level->IsWalkableFloor(intX, intY - 1)
			|| crossRight && crossFwd && !level->IsWalkableFloor(intX + 1, intY + 1)
			|| crossRight && crossBack && !level->IsWalkableFloor(intX + 1, intY - 1)
			|| crossLeft && crossFwd && !level->IsWalkableFloor(intX - 1, intY + 1)
			|| crossLeft && crossBack && !level->IsWalkableFloor(intX - 1, intY - 1))
		{
			return false;
		}
		return true;
	}

	void PlayerController::ConsumeInput()
	{
		mRequestedVelocity = glm::vec3(0.0f);
		mRequestedRotation = glm::vec3(0.0f);

		InputManager* inputManager = GGameEngine->GetInputManager();

		glm::vec3 playerPos = mPlayer->GetTransform().GetPosition();
		glm::mat4 playerRot = mPlayer->GetTransform().GetRotation();

		const glm::vec3 camForward = playerRot * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
		const glm::vec3 camRight = playerRot * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);

		if (inputManager->GetKey("w"))
		{
			mRequestedVelocity = camForward;
		}
		if (inputManager->GetKey("s"))
		{
			mRequestedVelocity = camForward * -1.0f;
		}
		if (inputManager->GetKey("d"))
		{
			mRequestedVelocity = camRight;
		}
		if (inputManager->GetKey("a"))
		{
			mRequestedVelocity = camRight * -1.0f;
		}
		if (inputManager->GetKey("e"))
		{
			mRequestedRotation = glm::vec3(0.0f, 0.0f, -1.0f);
		}
		if (inputManager->GetKey("q"))
		{
			mRequestedRotation = glm::vec3(0.0f, 0.0f, 1.0f);
		}
	}

}
