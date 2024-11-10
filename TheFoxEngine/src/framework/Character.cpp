#include "framework/Character.h"

namespace tf
{
	Character::Character(World* owningWorld, const std::string& texturePath)
		: Actor(owningWorld, texturePath),
		m_Velocity(sf::Vector2f()),
		m_Speed(60.f)
	{
	}

	void Character::BeginPlay()
	{
		Actor::BeginPlay();

		SetupAnimations();
		SetupInput();
	}
}