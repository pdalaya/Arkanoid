#include "pch.h"
#include "PowerUpPlayerSizeDown.h"

void Game::PowerUpPlayerSizeDown::ApplyEffect( std::shared_ptr<Game::PlayerRectangle> _playerPtr )
{
	_playerPtr->MultiplySize( .5f );
}



