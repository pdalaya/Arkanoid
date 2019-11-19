
#include "pch.h"
#include "Engine.h"

void Engine::ProcessInputs( float _deltaTime )
{
	sf::Event event;
	if ( m_window.pollEvent( event ) )
	{
		if ( !m_keyPressed && event.type == sf::Event::KeyPressed )
		{
			//Move Left
			if ( event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left )
				m_playerRectangle->SetVelocity( sf::Vector2f( -1, 0 ) );

			//Move Right
			if ( event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right )
				m_playerRectangle->SetVelocity( sf::Vector2f( 1, 0 ) );

			//Start
			if ( m_state == LEVEL_START && sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) )
			{
				m_balls [ 0 ]->Reset();
				m_state = MAIN;
			}

			//Restart
			if ( m_state == GAME_OVER && sf::Keyboard::isKeyPressed( sf::Keyboard::Space)  )
				RestartLevel( m_currentLevel == LEVEL_AMOUNT );

			//Change level
			if ( m_state == LEVEL_SUCCEEDED && sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) )
				ChangeLevel( ++m_currentLevel );

			// Debug MODE -> Cheat :). 
			if ( m_state != GAME_OVER && sf::Keyboard::isKeyPressed( sf::Keyboard::Tab ) )
			{
				LevelSucceeded();
			}

			m_keyPressed = true;
		}

		//Stop player and release key
		if ( m_keyPressed && event.type == sf::Event::KeyReleased )
		{
			m_playerRectangle->SetVelocity( sf::Vector2f( 0, 0 ) );
			m_keyPressed = false;
		}
	}

	// Handle the player quitting
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )
	{
		m_window.close();
	}

	
}


