#pragma once

#include <SFML/Graphics.hpp>

#include "framework/Core.h"
#include "framework/Object.h"

namespace tf
{
	class World;

	class Actor : public Object
	{
	public:
		Actor(World* owningWorld, const std::string& texturePath = "");

		virtual void SetToDestroy() override;

		void BeginPlayInternal();
		virtual void BeginPlay();

		void TickInternal(float deltaTime);
		virtual void Tick(float deltaTime);

		virtual void Render(sf::RenderWindow& window);
		void SetTexture(const std::string& texturePath);

		// Location
		sf::Vector2f GetActorLocation() const;
		void SetActorLocation(const sf::Vector2f& newPosition);

		// Rotation
		float GetActorRotation() const;
		void SetActorRotation(float newRotation);

		// Offsets
		void AddActorLocationOffset(const sf::Vector2f& offset);
		void AddActorRotationOffset(float offset);

		// Direction
		sf::Vector2f GetActorForwardDirection() const;
		sf::Vector2f GetActorRightDirection() const;

		// Bounds
		sf::FloatRect GetActorGlobalBounds() const;

		// World
		inline World* GetWorld() { return m_OwningWorld; }
		inline const World* GetWorld() const { return m_OwningWorld; }

		// Sprite
		inline sf::Sprite& GetSprite() { return m_Sprite; }
		inline const sf::Sprite& GetSprite() const { return m_Sprite; }

		Delegate<Actor*> onActorDestroyed;

	private:
		void CenterPivot();

		World* m_OwningWorld;
		bool m_BeganPlay;

		// Graphics
		sf::Sprite m_Sprite;
		shared<sf::Texture> m_Texture;
	};
}