#include "pch.h"
#include "Circle.h"
#include "Engine.h"

Game::Circle::Circle( const sf::Vector2f& _position, const sf::Vector2f& _size, const sf::Color& _fillColor )
{
	m_shape = new sf::CircleShape( _size.x, (size_t)_size.y ); 
	m_shape->setPosition( _position );
	m_shape->setFillColor( _fillColor );
}
