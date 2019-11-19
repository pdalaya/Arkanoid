#pragma once
#include "PowerUp.h"

namespace Game
{
	class PowerUpBallSpeedDown: public Game::PowerUp
	{
		using Game::PowerUp::PowerUp; //use the default constructor
	private:
		PowerUpBallSpeedDown(){};

		void ApplyEffect( std::shared_ptr<Game::PlayerRectangle> _playerPtr );

	public:
		~PowerUpBallSpeedDown(){};
	};
}
