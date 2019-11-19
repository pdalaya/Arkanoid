#include "pch.h"
#include "Engine.h"

void Engine::Update(float _deltaTime)
{
	switch ( m_state )
	{
		case LEVEL_START:
			m_playerRectangle->Update( _deltaTime );
			break;
		case MAIN:
			m_playerRectangle->Update( _deltaTime );

			//Power ups
			for ( size_t i = m_powerUps.size(); i--; )
			{
				if ( m_powerUps [ i ]->GetIsActive() == false )
					continue;

				m_powerUps [ i ]->Update( _deltaTime );
				IsCollidingWith( m_playerRectangle, m_powerUps[i] );
			}

			//Balls
			for ( size_t i = m_balls.size(); i--; )
			{
				IsCollidingWith( m_playerRectangle, m_balls [ i ] );

				for ( size_t j = m_bricks.size(); j--; )
				{
					if ( m_bricks [ j ]->isDestroyed() )
						continue;

					if ( IsCollidingWith( m_bricks [ j ], m_balls [ i ] ) )
					{
						if ( m_bricks [ j ]->isDestroyed() )
							OnBrickDestroyed( *m_bricks [ j ] );
					}
				}

				m_balls [ i ]->Update( _deltaTime , (int)i );
			}
			break;
		default:
			break;
	}
}


