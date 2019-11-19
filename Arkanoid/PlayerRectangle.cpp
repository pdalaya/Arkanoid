#include "pch.h"
#include "Engine.h"
#include <iostream>


Game::PlayerRectangle::PlayerRectangle( float _speed, const sf::Vector2f& _position, const sf::Vector2f& _size, const sf::Sprite& _sprite, const sf::Color& _fillColor )
	:Rectangle( _position, _size, _fillColor )
{
	m_speed = _speed;
	m_size = 1;
	m_sprite = _sprite;
	m_sprite.setScale( _size.x / m_sprite.getLocalBounds().width, _size.y / m_sprite.getLocalBounds().height );
}

void Game::PlayerRectangle::Update( float _deltaTime )
{
	//Prevents from going out of screen
	if ( ( GetLeft() < 0 && m_velocity.x < 0.f ) || ( GetRight() > WINDOW_WIDTH && m_velocity.x > 0.f ) )
		return;

	m_shape->move( m_velocity * _deltaTime  * m_speed );
	m_sprite.setPosition( m_shape->getPosition() );
}

void Game::PlayerRectangle::MultiplySize( float _multiplier )
{
	//few safety rules so we don't change size excessively
	if ( (_multiplier > 1 && m_size < 2 ) || (_multiplier < 1 && m_size > 0) ) 
	{
		sf::Vector2f newSize = sf::Vector2f( m_shape->getSize().x * _multiplier, m_shape->getSize().y );
		m_shape->setSize( newSize );
		m_sprite.setScale( newSize.x / m_sprite.getLocalBounds().width, newSize.y / m_sprite.getLocalBounds().height );

		m_size = _multiplier > 1 ? m_size + 1 : m_size - 1;
	}
}

void Game::PlayerRectangle::MultiplySpeed( float _multiplier )
{
	if ( ( _multiplier > 1 && m_speed <= PLAYER_SPEED ) || ( _multiplier < 1 && m_speed > PLAYER_SPEED / 2.f ) )
	{
		m_speed *= _multiplier;
	}
}
