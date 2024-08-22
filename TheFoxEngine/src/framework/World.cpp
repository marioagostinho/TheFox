#include "framework/Actor.h"
#include "framework/Application.h"
#include "framework/InputManager.h"

#include "framework/World.h"

namespace tf
{
	World::World(Application* owningApp)
		: m_OwningApp(owningApp),
		m_BeganPlay(false),
		m_Actors(),
		m_PendingActors()
	{
	}

	void World::BeginPlayInternal()
	{
		if (!m_BeganPlay)
		{
			m_BeganPlay = true;
			BeginPlay();
		}
	}

	void World::BeginPlay()
	{
		// Testing input
		InputManager& inputManager = InputManager::Get();

		inputManager.BindKey<World>(sf::Keyboard::A, -1, GetWeakRef(), 
			&World::OnMovementBeginPressed, &World::OnMovementPressed, &World::OnMovementEndPressed);
		inputManager.BindKey<World>(sf::Keyboard::D, 1, GetWeakRef(), 
			nullptr, &World::OnMovementPressed, nullptr);


	}

	void World::TickInternal(float deltaTime)
	{
		// Spawn pending actors
		if (m_PendingActors.size() > 0)
		{
			for (shared<Actor> actor : m_PendingActors)
			{
				m_Actors.push_back(actor);
				actor->BeginPlayInternal();
			}

			m_PendingActors.clear();
		}

		// Tick actors
		for (shared<Actor> actor : m_Actors)
		{
			actor->TickInternal(deltaTime);
		}

		Tick(deltaTime);
	}

	void World::Tick(float deltaTime)
	{
	}

	void World::Render(sf::RenderWindow& window)
	{
		for (shared<Actor> actor : m_Actors)
		{
			actor->Render(window);
		}
	}

	void World::CleanCycle()
	{
		for (auto iter = m_Actors.begin(); iter != m_Actors.end();)
		{
			if (iter->get()->IsPendingDestroy())
			{
				iter = m_Actors.erase(iter);
			}
			else
			{
				iter->get()->CleanCycle();
				++iter;
			}
		}
	}
	void World::OnMovementPressed(float value)
	{
		LOG("%f", value);
	}

	void World::OnMovementBeginPressed(float value)
	{
		LOG("Button Pressed");
	}

	void World::OnMovementEndPressed(float value)
	{
		LOG("Not Button Pressed anymore");
	}
}