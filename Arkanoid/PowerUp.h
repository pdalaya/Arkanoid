#pragma once
#include "Circle.h"
#include "PlayerRectangle.h"

enum PowerUpType
{
	PLAYER_SIZE_UP,
	PLAYER_SIZE_DOWN,
	MULTIPLE_BALLS,
	BALL_SPEED_UP,
	BALL_SPEED_DOWN,
	SUPER_BALL,
	POWER_UP_COUNT, //trick to get the count of the enum
};


namespace Game
{
	class PowerUp: public Game::Rectangle
	{
	private:

		float m_speed;
		sf::Sprite m_sprite;

		virtual void ApplyEffect( std::shared_ptr<Game::PlayerRectangle> _playerPtr ) = 0; //pure virtual function making this class abstract

	protected:
		bool m_isActive;

	public:
		PowerUp(){};
		PowerUp( float _speed, const sf::Vector2f& _position, const sf::Vector2f& _size, const sf::Sprite& _sprite, const sf::Color& _fillColor = sf::Color::White );
		virtual ~PowerUp(){};

		inline bool GetIsActive() const  {
			return m_isActive;
		}

		const sf::Sprite& GetSprite()	{
			return m_sprite;
		}

		virtual void Update( float _deltaTime );

		//void OnCollision( std::shared_ptr<Game::Shape> _otherShape );
		void OnCollision( std::shared_ptr<Game::Shape> _otherShape );

		static std::shared_ptr<Game::PowerUp> Create( PowerUpType _type, const sf::Vector2f& _position, const sf::Vector2f& _size, const sf::Sprite& _sprite );
	};
}