#pragma once

#include <SFML/Window.hpp>
#include <string>
#include "framework/Core.h"
#include "framework/Delegate.hpp"

namespace tf
{
	struct KeyMapping
	{
		map<sf::Keyboard::Key, float> KeyValueMap;
		Delegate<> onBeginPressed;
		Delegate<float> onPressed;
		Delegate<> onEndPressed;
		bool wasPressed = false;

		KeyMapping(map<sf::Keyboard::Key, float> keyValueMap)
		{
			KeyValueMap = keyValueMap;
		}
	};

	class InputManager
	{
	public:
		static InputManager& Get();

		template<typename T>
		void BindKey(map<sf::Keyboard::Key, float> keyValueMap,
			weak<Object> object,
			void(T::* onBeginPressed)() = nullptr,
			void(T::* onPressed)(float) = nullptr,
			void(T::* onEndPressed)() = nullptr);

		void HandleInput();

	protected:
		InputManager();

	private:
		static unique<InputManager> m_InputManager;

		 list<KeyMapping> m_KeyMappings;
	};

	template<typename T>
	void InputManager::BindKey(map<sf::Keyboard::Key, float> keyValueMap,
		weak<Object> object,
		void(T::* onBeginPressed)(),
		void(T::* onPressed)(float),
		void(T::* onEndPressed)())
	{
		KeyMapping mapping(keyValueMap);

		if (onBeginPressed)
		{
			mapping.onBeginPressed.BindAction(object, onBeginPressed);
		}

		if (onPressed)
		{
			mapping.onPressed.BindAction(object, onPressed);
		}

		if (onEndPressed)
		{
			mapping.onEndPressed.BindAction(object, onEndPressed);
		}

		m_KeyMappings.push_back(mapping);
	}
}