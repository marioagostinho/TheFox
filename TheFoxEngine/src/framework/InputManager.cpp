#include "framework/InputManager.h"

namespace tf
{
	unique<InputManager> InputManager::m_InputManager(nullptr);

	InputManager::InputManager()
		: m_KeyMappings()
	{
	}

	InputManager& InputManager::Get()
	{
		if (!m_InputManager)
		{
			m_InputManager = unique<InputManager>(new InputManager);
		}

		return *m_InputManager;
	}

	void InputManager::HandleInput()
	{
		for (auto& mapping : m_KeyMappings)
		{
			bool isCurrentlyPressed = sf::Keyboard::isKeyPressed(mapping.key);

			if (isCurrentlyPressed)
			{
				if (!mapping.wasPressed && mapping.onBeginPressed.IsBound())
				{
					mapping.onBeginPressed.Broadcast(mapping.value);
				}

				if (mapping.onPressed.IsBound())
				{
					mapping.onPressed.Broadcast(mapping.value);
				}
			}
			else if (mapping.wasPressed && !isCurrentlyPressed && mapping.onEndPressed.IsBound())
			{
				mapping.onEndPressed.Broadcast(mapping.value);
			}

			mapping.wasPressed = isCurrentlyPressed;
		}
	}
}