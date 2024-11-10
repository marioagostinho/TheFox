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
			float value = 0.f;
			bool isMapPressed = false;

			for (auto keyValue : mapping.KeyValueMap)
			{
				bool isKeyPressed = sf::Keyboard::isKeyPressed(keyValue.first);

				if (isKeyPressed)
				{
					value += keyValue.second;
					isMapPressed = true;
				}
			}

			if (isMapPressed)
			{
				if (!mapping.wasPressed && mapping.onBeginPressed.IsBound())
				{
					mapping.onBeginPressed.Broadcast();
				}

				if (mapping.onPressed.IsBound())
				{
					mapping.onPressed.Broadcast(value);
				}
			}
			else if (mapping.wasPressed && !isMapPressed && mapping.onEndPressed.IsBound())
			{
				mapping.onEndPressed.Broadcast();
			}

			mapping.wasPressed = isMapPressed;
		}
	}
}