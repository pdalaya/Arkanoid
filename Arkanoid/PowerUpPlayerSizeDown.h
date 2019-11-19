#pragma once
#include "PowerUp.h"

namespace Game
{
	class PowerUpPlayerSizeDown: public Game::PowerUp
	{
		using Game::PowerUp::PowerUp; //use the default constructor
	private:
		PowerUpPlayerSizeDown(){};

		void ApplyEffect( std::shared_ptr<Game::PlayerRectangle> _playerPtr );

	public:
		~PowerUpPlayerSizeDown(){};
	};
}
