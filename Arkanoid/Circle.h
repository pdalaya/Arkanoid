#pragma once
#include "Shape.h"

namespace Game
{
	class Circle : public Game::Shape
	{
	protected:
		sf::CircleShape* m_shape;
		Circle(){};

	public:
		Circle( const sf::Vector2f& _position, const sf::Vector2f& _size, const sf::Color& _fillColor  = sf::Color::White);
		virtual ~Circle(){
			delete m_shape;
		};

		float GetX() const {
			return GetLeft() + m_shape->getRadius();
		}
		float GetY() const {
			return GetTop() + m_shape->getRadius();
		}
		float GetLeft() const   {
			return m_shape->getPosition().x;
		}
		float GetRight()  const  {
			return GetLeft() + m_shape->getRadius() *2.f;
		}
		float GetTop()  const  {
			return m_shape->getPosition().y;
		}
		float GetBottom() const   {
			return GetTop() + m_shape->getRadius() *2.f;
		}

		sf::CircleShape* GetShape() const {
			return m_shape;
		}		
		
	};
}
