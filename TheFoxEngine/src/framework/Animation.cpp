#include "framework/AssetManager.h"
#include "framework/Animation.h"

namespace tf
{
	Animation::Animation(const std::string& texturePath, 
		int columns, int rows, float duration, sf::Sprite& sprite)
		: m_Columns(columns), m_Rows(rows), m_Duration(duration), m_Sprite(sprite), 
		 m_Texture(), m_ElapsedTime(0.f), m_CurrentFrame(0)
	{
		SetTexture(texturePath);
		m_FrameWidth = CalculateWidht();
		m_FrameHeight = CalculateHeight();
		CalculateFrames(m_Frames);
	}

	void Animation::PlayAnimation(float deltaTime)
	{
		if (m_Frames.size() <= 1)
			return;

		m_ElapsedTime += deltaTime;

		if (m_ElapsedTime >= m_Duration)
		{
			m_ElapsedTime -= m_Duration;
			m_CurrentFrame = (m_CurrentFrame + 1) % m_Frames.size();
			m_Sprite.setTextureRect(m_Frames[m_CurrentFrame]);
		}
	}

	void Animation::StopAnimation()
	{
		if (m_Frames.size() > 0)
		{
			m_CurrentFrame = 0;
			m_Sprite.setTextureRect(m_Frames[0]);
		}
	}

	void Animation::SetSprite(sf::Sprite& sprite)
	{
		m_Sprite = sprite;
		m_Sprite.setTexture(*m_Texture);
	}

	void Animation::SetTexture(const std::string& texturePath)
	{
		m_Texture = AssetManager::Get().LoadTexture(texturePath);

		if (m_Texture)
		{
			m_Sprite.setTexture(*m_Texture);

			int width = m_Texture->getSize().x;
			int height = m_Texture->getSize().y;
			m_Sprite.setTextureRect(sf::IntRect(sf::Vector2i(), sf::Vector2i(width, height)));

			CenterPivot();
		}
	}

	void Animation::CenterPivot()
	{
		sf::FloatRect bound = m_Sprite.getGlobalBounds();
		m_Sprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
	}

	float Animation::CalculateWidht()
	{
		if (!m_Texture)
			return 0.f;

		return m_Texture->getSize().x / m_Columns;
	}
	float Animation::CalculateHeight()
	{
		if (!m_Texture)
			return 0.f;

		return m_Texture->getSize().y / m_Rows;
	}

	void Animation::CalculateFrames(list<sf::IntRect>& frames)
	{
		if (m_FrameWidth == 0.f || m_FrameHeight == 0.f)
			return;

		for (int row = 0; row < m_Rows; ++row)
		{
			for (int column = 0; column < m_Columns; ++column)
			{
				frames.push_back(sf::IntRect(column * m_FrameWidth, row * m_FrameHeight,
					m_FrameWidth, m_FrameHeight));
			}
		}

		if (m_Frames.size() > 0)
		{
			m_Sprite.setTextureRect(m_Frames[0]);
		}
	}
}