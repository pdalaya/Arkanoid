#pragma once
#include <SFML/Graphics.hpp>

namespace Game
{
	//Abstract class
	class Shape
	{

	public:

		virtual float GetX() const = 0;
		virtual float GetY() const = 0;
		virtual float GetLeft() const = 0;
		virtual float GetRight()  const = 0;
		virtual float GetTop()  const  = 0;
		virtual float GetBottom() const = 0;

		virtual void OnCollision( std::shared_ptr<Game::Shape> _otherShape ) = 0;

		Shape(){};		
		virtual ~Shape(){};
	};
}
