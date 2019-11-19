#include "pch.h"
#include "Brick.h"
#include "Engine.h"

Game::Brick::Brick( int _hp, const sf::Vector2f& _position, const sf::Vector2f& _size ,const sf::Color& _fillColor )
	:Rectangle( _position, _size, _fillColor )
{
	m_hitPoints = _hp;
	m_shape->setOutlineColor( sf::Color::Black );
	m_shape->setOutlineThickness( 2);
}

void Game::Brick::OnCollision( std::shared_ptr<Game::Shape> _otherShape )
{
	m_hitPoints--;

	//Play Sound
	if (isDestroyed() == false)
		Engine::GetInstance()->PlaySound( SoundName::BALL_COLLISION );
}

