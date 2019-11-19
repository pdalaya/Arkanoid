#include "pch.h"
#include "PowerUpSuperBall.h"
#include "Engine.h"

void Game::PowerUpSuperBall::ApplyEffect( std::shared_ptr<Game::PlayerRectangle> _playerPtr )
{
	Engine::GetInstance()->ActivateSuperBall();
}



