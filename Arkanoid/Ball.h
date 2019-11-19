#pragma once
#include "Circle.h"

namespace Game
{
	class Ball: public Game::Circle
	{
	private:
		//used to decide if we bounce off brick or not
		bool m_ignoreBrickReflection;
		float m_speed;
		sf::Vector2f m_velocity;

		//needed when we reset the ball
		sf::Vector2f m_initialPosition;
		sf::Sprite m_sprite;

		//added to prevent the ball from colliding several times with the player and creating jiterring
		float m_collisionTimer; 

		Ball(){};

	public:
		Ball( float _speed, const sf::Vector2f& _position, const sf::Vector2f& _size, const sf::Sprite& _sprite, const sf::Color& _fillColor = sf::Color::White, const sf::Vector2f& _velocity = sf::Vector2f(0,0));
		~Ball(){};

		const sf::Sprite& GetSprite()	{
			return m_sprite;
		}

		void SetPosition( sf::Vector2f _position )
		{
			m_shape->setPosition( _position );
		}

		void SetIgnoreBrickReflection( bool _value )
		{
			m_ignoreBrickReflection = _value;
		}

		void Reset();
		void Update( float _deltaTime , int i );
		void MultiplySpeed( float _multiplier );
		void OnCollision( std::shared_ptr<Game::Shape> _otherShape );
	};

}