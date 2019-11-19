
#include "pch.h"
#include "Engine.h"

void Engine::Draw()
{
	// Clear last frame
	m_window.clear( sf::Color::White );

	//background
	m_window.draw( m_backgroundSprite );
	
	if ( m_state != State::LEVEL_START && m_state != State::LEVEL_SUCCEEDED )
	{
		//balls
		for ( size_t i = m_balls.size(); i--; )
		{
			m_window.draw( m_balls [ i ]->GetSprite());
		}

		//power ups
		for ( size_t i = m_powerUps.size(); i--; )
		{
			if ( m_powerUps [ i ]->GetIsActive() == false )
				continue;

			m_window.draw( m_powerUps [ i ]->GetSprite() );
		}
	}

	//Player
	m_window.draw( m_playerRectangle->GetSprite() );

	//Bricks
	for ( size_t i = m_bricks.size(); i--; )
	{
		if (m_bricks[i]->isDestroyed())
			continue;

		m_window.draw( *m_bricks [ i ]->GetShape() );
	}

	//Life UI
	for ( size_t i = m_lifeSprites.size(); i--;) 
	{
		m_window.draw(m_lifeSprites [ i ]);
	}

	//Text
	switch ( m_state )
	{
		case LEVEL_START:
			m_window.draw( m_startText );

			if (!m_firstLevelSucceeded)
				m_window.draw( m_keyBindingsText );

			m_window.draw( m_levelText );
			break;
		case LEVEL_SUCCEEDED:
			m_window.draw( m_levelSucceededText );
			m_window.draw( m_startText );
			break;
		case GAME_OVER:
			m_window.draw( m_gameOverText );
			m_window.draw( m_restartText );
			break;
		default:
			break;
	}


	//Score
	m_window.draw( m_scoreLabelText );
	m_window.draw( m_scoreValueText );

	// Show everything we have just drawn
	m_window.display();
}


