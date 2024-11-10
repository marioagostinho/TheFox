#include <framework/AnimationComponent.h>
#include <framework/Animation.h>
#include <framework/InputManager.h>

#include "player/Player.h"

namespace tf
{
	Player::Player(World* owningWorld)
		: Character(owningWorld)
	{
	}

	void Player::BeginPlay()
	{
		Character::BeginPlay();
	}

	void Player::Tick(float deltaTime)
	{
		AddActorLocationOffset(m_Velocity * deltaTime);
	}

	void Player::SetupAnimations()
	{
		AnimMap animations = {
			{ "idle", std::make_shared<Animation>("Characters/Fox/Idle.png", 11, 1, 0.09f, m_Sprite) },
			{ "run", std::make_shared<Animation>("Characters/Fox/Run.png", 12, 1, 0.083f, m_Sprite) }
		};

		m_AnimationComponent = AttachToActor<AnimationComponent>(animations);
		m_AnimationComponent.lock()->PlayAnimationByName("idle");
	}

	void Player::SetupInput()
	{
		InputManager& inputManager = InputManager::Get();

		inputManager.BindKey<Player>(
			{
				{sf::Keyboard::A, -1.f},
				{sf::Keyboard::D, 1.f}
			},
			GetWeakRef(),
			nullptr, & Player::OnMovementPressed, & Player::OnMovementEnded);
	}

	void Player::OnMovementPressed(float value)
	{
		m_AnimationComponent.lock()->PlayAnimationByName("run");

		m_Velocity = sf::Vector2f(value * m_Speed, 0.f);

		if (value != 0.f)
		{
			m_Sprite.setScale(value, 1.f);
		}
	}

	void Player::OnMovementEnded()
	{
		LOG("Not pressing map");

		m_AnimationComponent.lock()->PlayAnimationByName("idle");
		m_Velocity = sf::Vector2f(0.f, 0.f);
	}
}