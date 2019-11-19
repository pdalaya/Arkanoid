#include "pch.h"
#include "PowerUpBallSpeedDown.h"
#include "Engine.h"


void Game::PowerUpBallSpeedDown::ApplyEffect( std::shared_ptr<Game::PlayerRectangle> _playerPtr )
{
	Engine::GetInstance()->MultiplyBallsSpeed( BALL_SPEED_SLOWDOWN_FACTOR );
}



