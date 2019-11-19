#pragma once
#include "Shape.h"

namespace Game
{
	class Rectangle : public Game::Shape
	{
	protected:	
		sf::RectangleShape* m_shape;
		Rectangle(){};

	public:
		Rectangle( const sf::Vector2f& _position, const sf::Vector2f& _size, const sf::Color& _fillColor );
		virtual ~Rectangle(){
			delete m_shape;
		};

		inline float GetX() const {
			return GetLeft() + m_shape->getSize().x  *.5f;
		}
		inline float GetY() const {
			return GetTop() + m_shape->getSize().y  *.5f;
		}
		inline float GetLeft() const   {
			return m_shape->getPosition().x;
		}
		inline float GetRight()  const  {
			return GetLeft() + m_shape->getSize().x ;
		}
		inline float GetTop()  const  {
			return  m_shape->getPosition().y;
		}
		inline float GetBottom() const   {
			return GetTop() + m_shape->getSize().y;
		}

		sf::RectangleShape* GetShape()const  {
			return m_shape;
		}
	};
}
