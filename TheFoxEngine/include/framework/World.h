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

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		void Render(sf::RenderWindow& window);
		void CleanCycle();

		inline Application* GetApplication() { return m_OwningApp; }
		inline const Application* GetApplication() const { return m_OwningApp; }

	private:
		void BeginPlayInternal();
		void TickInternal(float deltaTime);

		Application* m_OwningApp;
		bool m_BeganPlay;

		list<shared<Actor>> m_Actors;
		list<shared<Actor>> m_PendingActors;
	};
}