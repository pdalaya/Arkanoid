#pragma once
#include "Rectangle.h"

namespace Game
{
	class Brick: public Game::Rectangle
	{

	private:
		int m_hitPoints;

	public:
		Brick(){};
		Brick( int _hp, const sf::Vector2f& _position, const sf::Vector2f& _size, const sf::Color& _fillColor = sf::Color::White );
		~Brick(){};

		inline bool isDestroyed()
		{
			return m_hitPoints <= 0;
		}

		inline int GetHp() const
		{
			return m_hitPoints;
		}

		void SetHp(int _value)
		{
			m_hitPoints = _value;
		}
		
		void OnCollision( std::shared_ptr<Game::Shape> _otherShape );
	};
}
