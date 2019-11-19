#include "pch.h"
#include "PowerUpBallSpeedUp.h"
#include "Engine.h"

void Game::PowerUpBallSpeedUp::ApplyEffect( std::shared_ptr<Game::PlayerRectangle> _playerPtr )
{
	Engine::GetInstance()->MultiplyBallsSpeed(  2 - BALL_SPEED_SLOWDOWN_FACTOR );
}



