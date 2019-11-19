#include "pch.h"
#include "SoundManager.h"
#include <iostream>

Game::SoundManager::SoundManager()
{
	//load all buffer
	m_ballCollisionBuffer.loadFromFile( "resources/Sounds/ballCollision.wav" );
	m_brickDestroyedBuffer.loadFromFile( "resources/Sounds/brickDestroyed.wav" );
	m_lifeLostBuffer.loadFromFile( "resources/Sounds/lifeLost.wav" );
	m_powerUpBuffer.loadFromFile( "resources/Sounds/powerUp.wav" );
	m_gameOverBuffer.loadFromFile( "resources/Sounds/gameOver.wav" );
	m_gameStartBuffer.loadFromFile( "resources/Sounds/gameStart.wav" );
	m_levelSucceededBuffer.loadFromFile( "resources/Sounds/levelSucceeded.wav" );
}

void Game::SoundManager::PlaySound( SoundName _soundName )
{
	//gets the first sound that is available
	for ( size_t i = 0; i < m_sounds.size(); i++)
	{
		if ( m_sounds [ i ].getStatus() == sf::Sound::Status::Stopped )
		{
			m_sounds [ i ].setBuffer( GetBuffer( _soundName ) );
			m_sounds [ i ].setVolume( 100 );
			m_sounds [ i ].play();
			return;
		}
	}
}

const sf::SoundBuffer& Game::SoundManager::GetBuffer( SoundName _soundName )
{
	switch ( _soundName )
	{
		case BALL_COLLISION:
			return m_ballCollisionBuffer;
		case BRICK_DESTROYED:
			return m_brickDestroyedBuffer;
		case LIFE_LOST:
			return m_lifeLostBuffer;
		case POWER_UP:
			return m_powerUpBuffer;
		case GAME_OVER:
			return m_gameOverBuffer;
		case GAME_START:
			return m_gameStartBuffer;
		case LEVEL_SUCCEEDED:
			return m_levelSucceededBuffer;
	}

	return m_ballCollisionBuffer;
}

