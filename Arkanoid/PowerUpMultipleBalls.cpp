#include "pch.h"
#include "PowerUpMultipleBalls.h"
#include "Engine.h"


Game::PowerUpMultipleBalls::PowerUpMultipleBalls( float _speed, const sf::Vector2f& _position, const sf::Vector2f& _size, const sf::Sprite& _sprite, const sf::Color& _fillColor)
	:PowerUp( _speed, _position, _size, _sprite ,_fillColor )
{
	m_ballAmount = 2;
}

void Game::PowerUpMultipleBalls::ApplyEffect( std::shared_ptr<Game::PlayerRectangle> _playerPtr )
{
	for ( size_t i = 0; i < m_ballAmount; i++ )
	{
		float multiplier = i % 2 == 0 ? -1.f : 1.f; //alternate x velocity 
		Engine::GetInstance()->CreateDuplicateBall( sf::Vector2f( multiplier, -1 ) );
	}	
}



