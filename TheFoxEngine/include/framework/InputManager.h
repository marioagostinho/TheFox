#pragma once

#include <SFML/Window.hpp>
#include <string>
#include "framework/Core.h"
#include "framework/Delegate.hpp"

namespace tf
{
	enum class InputSate
	{
		BeginPressed,
		Pressed,
		EndPressed
	};

	struct KeyMapping
	{
		sf::Keyboard::Key key;
		float value;
		Delegate<float> onBeginPressed;
		Delegate<float> onPressed;
		Delegate<float> onEndPressed;
		bool wasPressed = false;
	};

	class InputManager
	{
	public:
		static InputManager& Get();

		template<typename T>
		void BindKey(sf::Keyboard::Key key, float value,
			weak<Object> object,
			void(T::* onBeginPressed)(float) = nullptr,
			void(T::* onPressed)(float) = nullptr,
			void(T::* onEndPressed)(float) = nullptr);

		void HandleInput();

	protected:
		InputManager();

	private:
		static unique<InputManager> m_InputManager;

		 list<KeyMapping> m_KeyMappings;
	};

	template<typename T>
	void InputManager::BindKey(sf::Keyboard::Key key, float value,
		weak<Object> object,
		void(T::* onBeginPressed)(float),
		void(T::* onPressed)(float),
		void(T::* onEndPressed)(float))
	{
		KeyMapping mapping = { key, value };

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