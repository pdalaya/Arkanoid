#pragma once
#include "PowerUp.h"

namespace Game
{
	class PowerUpSuperBall: public Game::PowerUp
	{
		using Game::PowerUp::PowerUp; //use the default constructor
	private:
		PowerUpSuperBall(){};

		void ApplyEffect( std::shared_ptr<Game::PlayerRectangle> _playerPtr );

	public:
		~PowerUpSuperBall(){};
	};
}
