#pragma once

#include <framework/Character.h>

namespace tf 
{
	class Player : public Character
	{
	public:
		Player(World* owningWorld);
		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;

	private:
		virtual void SetupAnimations() override;
		virtual void SetupInput() override;

		void OnMovementPressed(float value);
		void OnMovementEnded();
	};
}