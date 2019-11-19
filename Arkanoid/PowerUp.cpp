#include "pch.h"
#include "PowerUp.h"
#include "Engine.h"
#include "PowerUpPlayerSizeUp.h"
#include "PowerUpPlayerSizeDown.h"
#include "PowerUpMultipleBalls.h"
#include "PowerUpBallSpeedUp.h"
#include "PowerUpBallSpeedDown.h"
#include "PowerUpSuperBall.h"



Game::PowerUp::PowerUp( float _speed, const sf::Vector2f& _position, const sf::Vector2f& _size, const sf::Sprite& _sprite, const sf::Color& _fillColor  )
	:Rectangle( _position, _size, _fillColor )
{
	m_isActive = true;
	m_speed = _speed;
	m_shape->setPosition( _position );
	m_sprite = _sprite;
	m_sprite.setScale( _size.x / _sprite.getLocalBounds().width, _size.y / _sprite.getLocalBounds().height );
	m_sprite.setPosition( _position );
}


void Game::PowerUp::Update( float _deltaTime )
{
	//if the power up falls at the bottom of the window
	if ( GetTop() > WINDOW_HEIGHT )
	{
		m_isActive = false;
	}

	m_shape->move( sf::Vector2f( 0, 1 ) * _deltaTime  * m_speed );
	m_sprite.setPosition( m_shape->getPosition() );
}

void Game::PowerUp::OnCollision( std::shared_ptr <Game::Shape> _otherShape )
{
	std::shared_ptr<Game::PlayerRectangle> playerPtr = std::dynamic_pointer_cast< Game::PlayerRectangle > ( _otherShape );

	//Collide with player
	if ( playerPtr != nullptr )
	{
		ApplyEffect( playerPtr );

		//One sound for all power ups. Normally this would be in the Apply Effect of the child so they would have a custom sound for each power up.
		Engine::GetInstance()->PlaySound( Game::SoundName::POWER_UP );

		m_isActive = false;
	}
}

std::shared_ptr<Game::PowerUp> Game::PowerUp::Create( PowerUpType _type, const sf::Vector2f& _position, const sf::Vector2f& _size, const sf::Sprite& _sprite )
{
	float speed = rand() % 200 + 150.f ; // random speed. Surprises the player.

	switch ( _type )
	{
		case PLAYER_SIZE_UP:
			return std::make_shared<Game::PowerUpPlayerSizeUp>( speed, _position, _size, _sprite );
		case PLAYER_SIZE_DOWN:
			return std::make_shared<Game::PowerUpPlayerSizeDown>( speed, _position, _size, _sprite );
		case MULTIPLE_BALLS:
			return std::make_shared<Game::PowerUpMultipleBalls>( speed, _position, _size, _sprite);
		case BALL_SPEED_UP:
			return std::make_shared<Game::PowerUpBallSpeedUp>( speed, _position, _size, _sprite );
		case BALL_SPEED_DOWN:
			return std::make_shared<Game::PowerUpBallSpeedDown>( speed, _position, _size, _sprite );
		case SUPER_BALL:
			return std::make_shared<Game::PowerUpSuperBall>( speed, _position, _size, _sprite );
		default:
			return std::make_shared<Game::PowerUpMultipleBalls>( speed, _position, _size, _sprite );
	}

	return nullptr;
}

