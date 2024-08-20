#pragma once

#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/Math.h"

#include "framework/Actor.h"

namespace tf
{
	Actor::Actor(World* owningWorld, const std::string& texturePath)
		: m_OwningWorld(owningWorld),
		m_BeganPlay(false),
		m_Sprite(),
		m_Texture()
	{
		SetTexture(texturePath);
	}

	void Actor::SetToDestroy()
	{
		onActorDestroyed.Broadcast(this);
		Object::SetToDestroy();
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
		if (!IsPendingDestroy())
		{
			Tick(deltaTime);
		}
	}
	void Actor::Tick(float deltaTime)
	{
	}

	void Actor::SetTexture(const std::string& texturePath)
	{
		if (m_Texture = AssetManager::Get().LoadTexture(texturePath)) 
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