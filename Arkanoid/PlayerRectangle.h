#pragma once
#include "Rectangle.h"

namespace Game
{
	class PlayerRectangle: public Rectangle
	{
	private:
		sf::Sprite m_sprite;
		sf::Vector2f m_velocity;
		float m_speed;

		//keeps track of which size we are so we don't go overboard. I had first 4 different sizes...but now I only have two so this is probably not needed anymore
		int m_size;

	public:
		PlayerRectangle( float _speed, const sf::Vector2f& _position, const sf::Vector2f& _size, const sf::Sprite& _sprite, const sf::Color& _fillColor  = sf::Color ::White);
		~PlayerRectangle(){};

		inline float GetSpeed( ) const {
			return m_speed;
		}

		void SetVelocity( sf::Vector2f _velocity )    
		{
			m_velocity = _velocity;
		}

		const sf::Sprite& GetSprite() {
			return m_sprite;
		}

		void Update( float _deltaTime );		

		void OnCollision( std::shared_ptr<Game::Shape> _otherShape ){}; 

		void MultiplySpeed( float _multiplier );
		void MultiplySize( float _multiplier );
	};
}