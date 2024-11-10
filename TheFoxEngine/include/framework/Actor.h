#pragma once

#include <SFML/Graphics.hpp>

#include "framework/Core.h"
#include "framework/Object.h"

namespace tf
{
	class World;
	class ActorComponent;

	class Actor : public Object
	{
	public:
		Actor(World* owningWorld, const std::string& texturePath = "");

		void BeginPlayInternal();
		virtual void BeginPlay();

		void TickInternal(float deltaTime);
		virtual void Tick(float deltaTime);

		inline const bool IsTickEnabled() const { return m_TickEnabled; }
		inline void SetTickEnabled(bool ticking) { m_TickEnabled = ticking; }

		// Components
		template<typename T, typename... Args>
		weak<T> AttachToActor(Args... args);
		void CleanCycle();

		virtual void Render(sf::RenderWindow& window);
		void SetTexture(const std::string& texturePath);

		sf::Vector2f GetActorLocation() const;
		void SetActorLocation(const sf::Vector2f& newPosition);

		float GetActorRotation() const;
		void SetActorRotation(float newRotation);

		void AddActorLocationOffset(const sf::Vector2f& offset);
		void AddActorRotationOffset(float offset);

		sf::Vector2f GetActorForwardDirection() const;
		sf::Vector2f GetActorRightDirection() const;

		sf::FloatRect GetActorGlobalBounds() const;

		inline sf::Sprite& GetSprite() { return m_Sprite; }
		inline const sf::Sprite& GetSprite() const { return m_Sprite; }

		inline World* GetWorld() { return m_OwningWorld; }
		inline const World* GetWorld() const { return m_OwningWorld; }

	protected:
		virtual void SetupInput();

		sf::Sprite m_Sprite;

	private:
		void CenterPivot();

		World* m_OwningWorld;
		bool m_BeganPlay;
		bool m_TickEnabled;

		list<shared<ActorComponent>> m_ActorComponents;
		list<shared<ActorComponent>> m_PendingActorComponents;

		shared<sf::Texture> m_Texture;
	};

	template<typename T, typename... Args>
	weak<T> Actor::AttachToActor(Args... args)
	{
		shared<T> newActorComponent{ new T(this, args...) };
		m_PendingActorComponents.push_back(newActorComponent);
		return newActorComponent;
	}
}