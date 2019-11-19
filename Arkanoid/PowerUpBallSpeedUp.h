#pragma once
#include "PowerUp.h"

namespace Game
{
	class PowerUpBallSpeedUp: public Game::PowerUp
	{
		using Game::PowerUp::PowerUp; //use the default constructor
	private:
		PowerUpBallSpeedUp(){};

		void ApplyEffect( std::shared_ptr<Game::PlayerRectangle> _playerPtr );

	public:
		~PowerUpBallSpeedUp(){};
	};
}
