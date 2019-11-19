#include "pch.h"
#include "PowerUpPlayerSizeUp.h"

void Game::PowerUpPlayerSizeUp::ApplyEffect( std::shared_ptr<Game::PlayerRectangle> _playerPtr )
{
	_playerPtr->MultiplySize( 2 );
}



