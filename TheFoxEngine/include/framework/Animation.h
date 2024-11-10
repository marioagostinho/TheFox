#pragma once

#include <SFML/Graphics.hpp>
#include "framework/Core.h"
#include "framework/Object.h"

namespace tf
{
	class Animation : public Object
	{
	public:
		Animation(const std::string& texturePath, int columns, int rows, float duration, sf::Sprite& sprite);

		void PlayAnimation(float deltaTime);
		void StopAnimation();

		void SetSprite(sf::Sprite& sprite);

		Delegate<Animation*> onAnimationEnded;

	private:
		void SetTexture(const std::string& texturePath);
		void CalculateFrames(list<sf::IntRect>& frames);

		sf::Sprite& m_Sprite;
		shared<sf::Texture> m_Texture;
		list<sf::IntRect> m_Frames;
		float m_FrameWidth;
		float m_FrameHeight;
		unsigned int m_Columns;
		unsigned int m_Rows;
		float m_Duration;
		float m_ElapsedTime;
		unsigned int m_CurrentFrame;
	};

	using AnimMap = map<std::string, shared<Animation>>;
}