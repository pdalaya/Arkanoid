#include "pch.h"
#include "Rectangle.h"
#include "Engine.h"

Game::Rectangle::Rectangle( const sf::Vector2f& _position, const sf::Vector2f& _size, const sf::Color& _fillColor )
{
	m_shape = new sf::RectangleShape( _size );
	m_shape->setPosition( _position );
	m_shape->setFillColor( _fillColor );
}