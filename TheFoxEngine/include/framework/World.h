#pragma once

#include <SFML/Graphics.hpp>

#include "framework/Object.h"
#include "framework/Core.h"

namespace tf
{
	class Application;
	class Actor;

	class World : public Object
	{
	public:
		World(Application* owningApp);

		void BeginPlayInternal();
		virtual void BeginPlay();

		void TickInternal(float deltaTime);
		virtual void Tick(float deltaTime);
		void Render(sf::RenderWindow& window);
		void CleanCycle();

		template<typename T, typename... Args>
		weak<T> SpawnActor(Args... args);

		inline Application* GetApplication() { return m_OwningApp; }
		inline const Application* GetApplication() const { return m_OwningApp; }

	private:
		void OnMovementPressed(float value);
		void OnMovementBeginPressed(float value);
		void OnMovementEndPressed(float value);

		Application* m_OwningApp;
		bool m_BeganPlay;

		list<shared<Actor>> m_Actors;
		list<shared<Actor>> m_PendingActors;
	};

	template<typename T, typename... Args>
	weak<T> World::SpawnActor(Args... args)
	{
		shared<T> newActor{ new T(this, args...) };
		m_PendingActors.push_back(newActor);
		return newActor;
	}
}