#pragma once
#include "PowerUp.h"

namespace Game
{
	class PowerUpPlayerSizeUp:	public Game::PowerUp
	{
		using Game::PowerUp::PowerUp; //use the default constructor
	private:
		PowerUpPlayerSizeUp(){};

		void ApplyEffect( std::shared_ptr<Game::PlayerRectangle> _playerPtr );

	public:
		~PowerUpPlayerSizeUp(){};
	};
}
