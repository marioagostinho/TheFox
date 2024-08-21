#pragma once

#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/Math.h"
#include "framework/ActorComponent.h"
#include "framework/Animation.h"
#include "framework/AnimationComponent.h"

#include "framework/Actor.h"

namespace tf
{
	Actor::Actor(World* owningWorld, const std::string& texturePath)
		: m_OwningWorld(owningWorld),
		m_BeganPlay(false),
		m_TickEnabled(true),
		m_Sprite(),
		m_Texture()
	{
		SetTexture(texturePath);

		map<std::string, shared<Animation>> animations = {
			{ "idle", std::make_shared<Animation>("Characters/Fox/Idle.png", 11, 1, 0.09f, m_Sprite) },
			{ "run", std::make_shared<Animation>("Characters/Fox/Run.png", 12, 1, 0.083f, m_Sprite) }
		};

		weak<AnimationComponent> aniComp = AttachToActor<AnimationComponent>(animations);
		aniComp.lock()->PlayAnimation("run");
	}

	void Actor::BeginPlayInternal()
	{
		if (!m_BeganPlay)
		{
			m_BeganPlay = true;
			BeginPlay();
		}
	}

	void Actor::BeginPlay()
	{
	}

	void Actor::TickInternal(float deltaTime)
	{
		if (IsPendingDestroy() && !m_TickEnabled)
			return;

		// Spawn pending actor components
		if (m_PendingActorComponents.size() > 0)
		{
			for (shared<ActorComponent> component : m_PendingActorComponents)
			{
				m_ActorComponents.push_back(component);
				component->BeginPlayInternal();
			}

			m_PendingActorComponents.clear();
		}

		// Tick actor components
		for (shared<ActorComponent> component : m_ActorComponents)
		{
			component->TickInternal(deltaTime);
		}
		
		Tick(deltaTime);
	}
	void Actor::Tick(float deltaTime)
	{
	}

	void Actor::CleanCycle()
	{
		for (auto iter = m_ActorComponents.begin(); iter != m_ActorComponents.end();)
		{
			if (iter->get()->IsPendingDestroy())
			{
				iter = m_ActorComponents.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}

	void Actor::SetTexture(const std::string& texturePath)
	{
		if (texturePath == "")
			return;

		m_Texture = AssetManager::Get().LoadTexture(texturePath);

		if (m_Texture);
		{
			m_Sprite.setTexture(*m_Texture);

			int width = m_Texture->getSize().x;
			int height = m_Texture->getSize().y;
			m_Sprite.setTextureRect(sf::IntRect(sf::Vector2i(), sf::Vector2i(width, height)));

			CenterPivot();
		}
	}

	void Actor::CenterPivot()
	{
		sf::FloatRect bound = m_Sprite.getGlobalBounds();
		m_Sprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
	}

	void Actor::Render(sf::RenderWindow& window)
	{
		if (!IsPendingDestroy())
		{
			window.draw(m_Sprite);
		}
	}

	sf::Vector2f Actor::GetActorLocation() const
	{
		return m_Sprite.getPosition();
	}

	void Actor::SetActorLocation(const sf::Vector2f& newPosition)
	{
		m_Sprite.setPosition(newPosition);
	}

	float Actor::GetActorRotation() const
	{
		return m_Sprite.getRotation();
	}

	void Actor::SetActorRotation(float newRotation)
	{
		m_Sprite.setRotation(newRotation);
	}

	void Actor::AddActorLocationOffset(const sf::Vector2f& offset)
	{
		SetActorLocation(GetActorLocation() + offset);
	}

	void Actor::AddActorRotationOffset(float offset)
	{
		SetActorRotation(GetActorRotation() + offset);
	}

	sf::Vector2f Actor::GetActorForwardDirection() const
	{
		return RotationToVector(GetActorRotation());
	}

	sf::Vector2f Actor::GetActorRightDirection() const
	{
		return RotationToVector(GetActorRotation() + 90.f);
	}

	sf::FloatRect Actor::GetActorGlobalBounds() const
	{
		return m_Sprite.getGlobalBounds();
	}
}