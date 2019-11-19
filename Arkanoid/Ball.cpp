#include "pch.h"
#include "Ball.h"
#include "Engine.h"

Engine* Engine::m_instance;


Game::Ball::Ball( float _speed, const sf::Vector2f& _position, const sf::Vector2f& _size, const sf::Sprite& _sprite, const sf::Color& _fillColor, const sf::Vector2f& _velocity )
	: Circle( _position, _size, _fillColor )
{
	m_speed = _speed;
	m_initialPosition = _position;
	m_velocity = _velocity;
	m_sprite = _sprite;
	m_sprite.setScale( _size.x * 2 / m_sprite.getLocalBounds().width, _size.x *2 / m_sprite.getLocalBounds().height );
	m_sprite.setColor( _fillColor );
}

void Game::Ball::MultiplySpeed( float _multiplier )
{
	if ( ( _multiplier > 1 && m_speed <= BALL_SPEED ) || ( _multiplier < 1 && m_speed > BALL_SPEED * BALL_SPEED_SLOWDOWN_FACTOR ) )
	{
		m_speed *= _multiplier;
	}
}

void Game::Ball::Update( float _deltaTime, int i )
{
	//Prevents from going out of screen
	if ( GetLeft() < 0 || GetRight() > WINDOW_WIDTH )
	{
		m_velocity.x *= -1;
		Engine::GetInstance()->PlaySound( SoundName::BALL_COLLISION );
	}
	else if ( GetTop() < 0 )
	{
		m_velocity.y *= -1;
		Engine::GetInstance()->PlaySound( SoundName::BALL_COLLISION );
	}

	//if the balls falls at the bottom of the window
	if ( GetTop() > WINDOW_HEIGHT )
	{
		if ( Engine::GetInstance()->CanRemoveALife(i) )
			Reset();
	}

	//small delay to avoid mutliple collision with the player
	if ( m_collisionTimer > 0 )
	{
		m_collisionTimer -= _deltaTime;
	}

	m_shape->move( m_velocity * _deltaTime  * m_speed );
	m_sprite.setPosition( m_shape->getPosition() );
}

void Game::Ball::Reset()
{
	m_shape->setPosition( m_initialPosition );
	m_sprite.setPosition( m_initialPosition );
	m_velocity = sf::Vector2f( 0, -1 );
	m_ignoreBrickReflection = false;
	m_speed = BALL_SPEED;
	m_collisionTimer = 0;
}

void Game::Ball::OnCollision( std::shared_ptr<Game::Shape> _otherShape )
{
	std::shared_ptr<Game::PlayerRectangle> playerPtr = std::dynamic_pointer_cast< Game::PlayerRectangle > ( _otherShape );
	   
	//Collide with player
	if ( playerPtr != nullptr && m_collisionTimer <= 0 )
	{
		m_velocity.y *= -1;
		m_velocity.x = ( GetX() - playerPtr->GetX() ) / ( playerPtr->GetShape()->getSize().x / 2 ) * 2;
		m_collisionTimer = 1.f;

		//PlaySound
		Engine::GetInstance()->PlaySound( SoundName::BALL_COLLISION );
	}

	std::shared_ptr<Game::Brick> brickPtr = std::dynamic_pointer_cast< Game::Brick > ( _otherShape );

	if ( brickPtr != nullptr && m_ignoreBrickReflection == false)
	{
		//Check all overlap values
		float overlapLeft = GetRight() - brickPtr->GetLeft();
		float overlapRight = brickPtr->GetRight() - GetLeft();
		float overlapTop = GetBottom() - brickPtr->GetTop();
		float overlapBottom = brickPtr->GetBottom() - GetTop();

		//determines where the ball comes from
		bool ballFromLeft = abs( overlapLeft ) < abs( overlapRight );
		bool ballFromTop = abs( overlapTop ) < abs( overlapBottom );

		// choose witch value we will use based on where the ball comes from
		float overlapX = ballFromLeft ? overlapLeft : overlapRight;
		float overlapY = ballFromTop ? overlapTop : overlapBottom;

		//compares the overlap on the x axis to the overlap on the y axis.
		//if the overlap x is < than the overlap y, this means that the ball is coming from the sides.
		if ( abs( overlapX ) < abs( overlapY ) )
		{
			//flip x
			sf::Vector2f newVelocity = m_velocity * sf::Vector2f( -1, 1 );
			m_velocity = newVelocity;
		}
		else
		{
			//flip y
			sf::Vector2f newVelocity = m_velocity * sf::Vector2f( 1, -1 );
			m_velocity = newVelocity;
		}
	}
}