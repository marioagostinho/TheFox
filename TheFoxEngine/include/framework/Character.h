#pragma once

#include "framework/Actor.h"

namespace tf
{
	class AnimationComponent;

	class Character : public Actor
	{
	public:
		Character(World* owningWorld, const std::string& texturePath = "");
		virtual void BeginPlay() override;

	protected:
		weak<AnimationComponent> m_AnimationComponent;

		sf::Vector2f m_Velocity;
		float m_Speed;

	private:
		virtual void SetupAnimations() = 0;
		virtual void SetupInput() = 0;
	};
}