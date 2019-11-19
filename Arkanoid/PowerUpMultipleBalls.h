#pragma once
#include "PowerUp.h"

namespace Game
{
	class PowerUpMultipleBalls: public Game::PowerUp
	{
	private:
		PowerUpMultipleBalls(){};

		unsigned int m_ballAmount;

		void ApplyEffect( std::shared_ptr<Game::PlayerRectangle> _playerPtr );

	public:
		PowerUpMultipleBalls( float _speed, const sf::Vector2f& _position, const sf::Vector2f& _size, const sf::Sprite& _sprite, const sf::Color& _fillColor = sf::Color::White );
		~PowerUpMultipleBalls(){};
	};
}
