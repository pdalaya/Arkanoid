#include "pch.h"
#include "Engine.h"
#include <iostream>
#include <sstream>
#include "PowerUp.h"

Engine::Engine( int width, int height )
{
	m_window.create( sf::VideoMode( width, height ), "Arkanoid", sf::Style::Resize );

	// Load the assets
	if ( m_backgroundTexture.loadFromFile( "resources/galaxy1.jpg" ) )
	{
		 m_backgroundSprite.setTexture( m_backgroundTexture );
		 m_backgroundSprite.setScale( WINDOW_WIDTH / m_backgroundSprite.getLocalBounds().width, WINDOW_HEIGHT / m_backgroundSprite.getLocalBounds().height );
	}
	m_spriteSheet.loadFromFile( "resources/spriteSheet.png" );
	m_font.loadFromFile( "resources/pixel.ttf" );

	//Load level templates
	for ( size_t i = 0; i < LEVEL_AMOUNT; i++ )
	{
		std::stringstream ss;
		ss << "resources/levelTemplate" << i << ".png";
		sf::Image img = sf::Image();

		if ( img.loadFromFile( ss.str() ) )
			m_levelTemplates.emplace_back( img );
	}

	//Set up texts
	FormatText( m_levelText, "Level : 1", m_font, 60, sf::Vector2f( WINDOW_WIDTH / 2 - 200, 0 ) );
	FormatText( m_startText, "Press 'Space' to start", m_font, 35, sf::Vector2f( WINDOW_WIDTH / 2 - 270, WINDOW_HEIGHT / 2.f ) );
	FormatText( m_gameOverText, "Game Over", m_font, 60, sf::Vector2f( WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2.f ) );
	FormatText( m_restartText, "Press 'Space' to play again", m_font, 20, sf::Vector2f( WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2.f + 100.f ) );
	FormatText( m_levelSucceededText, "Level Succeeded", m_font, 60, sf::Vector2f( WINDOW_WIDTH / 2 - 320, 0 ) );
	FormatText( m_keyBindingsText, "A/D or Arrows keys to move", m_font, 20, sf::Vector2f( WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2.f + 100.f ) );
	FormatText( m_scoreLabelText, "Score:", m_font, 25, sf::Vector2f( WINDOW_WIDTH - 200 , WINDOW_HEIGHT - 50.f ) );
	FormatText( m_scoreValueText, "0", m_font, 25, sf::Vector2f( WINDOW_WIDTH  - 100, WINDOW_HEIGHT - 50.f ) );

	//Lives
	m_lifeSprites.clear();
	for ( int i = 0; i < abs( INITIAL_LIFE_COUNT ); i++ )
	{
		AddLife();
	}

	//Cache useful dimensions (could also make properties)
	m_playerSize = sf::Vector2f( m_window.getSize().x / 9.f, m_window.getSize().x / 30.f );
	m_playerPosition = sf::Vector2f( m_window.getSize().x / 2.f - m_playerSize.x / 2, m_window.getSize().y - ( m_window.getSize().y / 10.f ) );
	m_ballSize = sf::Vector2f( m_window.getSize().x / 100.f, 30 );
	m_ballPosition = sf::Vector2f( m_window.getSize().x / 2.f - m_ballSize.x / 2, m_window.getSize().y - ( m_window.getSize().y / 8.f ) );
	m_brickSize = m_playerSize * .9f;

	//Set window's options
	m_window.setKeyRepeatEnabled( false );
	m_window.setFramerateLimit( 60 );
}

void Engine::Run()
{
	// Timing
	sf::Clock clock;

	SetupLevel();

	while ( m_window.isOpen() )
	{
		// Restart the clock and save the elapsed time into dt
		sf::Time dt = clock.restart();
		float deltaTtime = dt.asSeconds();

		ProcessInputs( deltaTtime );
		Update( deltaTtime );
		Draw();
	}
}

#pragma region Game Flow

void Engine::SetupLevel()
{
	//level text change  
	std::stringstream ss;
	ss << "Level : " << m_currentLevel + 1;
	m_levelText.setString( ss.str() );
	m_startText.setString( "Press 'Space' to start" );

	//Player
	m_playerRectangle = CreatePlayer();

	//balls
	m_balls.clear();
	m_balls.emplace_back( CreateBall( m_ballPosition ) );

	//bricks
	m_bricks.clear();
	SetUpBricks( m_currentLevel, sf::Vector2f( 40, 40 ), m_brickSize );
	m_destroyedBrickCount = 0; //reset

	//Power ups
	m_powerUps.clear();

	PlaySound( Game::SoundName::GAME_START );

	//Game State
	m_state = LEVEL_START;
}

void Engine::LevelSucceeded()
{
	//update texts
	m_levelSucceededText.setString( "Level Succeeded!" );
	m_startText.setString( "Press 'Space' to continue" );

	PlaySound( Game::SoundName::LEVEL_SUCCEEDED );

	if ( !m_firstLevelSucceeded )
		m_firstLevelSucceeded = true;

	m_state = State::LEVEL_SUCCEEDED;
}

void Engine::ChangeLevel( int _newLevel )
{
	m_currentLevel = _newLevel;

	//If we finish the game, game over. Otherwise continue on to the new level.
	if ( m_currentLevel == LEVEL_AMOUNT )
		GameOver();
	else
		SetupLevel();
}

void Engine::RestartLevel( bool _restartGame )
{
	//if we start from the beginning, reset the level and the score
	if ( _restartGame )
	{
		m_currentLevel = 0;
		SetScore( 0 );
	}

	//Reset lives to max
	m_lifeSprites.clear();
	for ( int i = 0; i < abs(INITIAL_LIFE_COUNT); i++ )
	{
		AddLife();
	}

	SetupLevel();
}

void Engine::GameOver()
{
	PlaySound( Game::SoundName::GAME_OVER );
	m_state = State::GAME_OVER;
}

//Get the information from the image's pixels. We want the color and the offset. 
void Engine::SetUpBricks( int _currentLevel, const sf::Vector2f& _offset, const sf::Vector2f& _size )
{
	//safety 
	if ( m_levelTemplates.size() == 0 )
	{
		std::cout << "No level templates include in the project!" << '\n';
		return;
	}

	int rows = m_levelTemplates [ _currentLevel ].getSize().y;
	int columns = m_levelTemplates [ _currentLevel ].getSize().x;

	if ( rows > 2000 || columns > 2000 )
		return;

	for ( int i = 0; i < rows; i++ )
	{
		for ( int j = 0; j < columns; j++ )
		{
			sf::Color pixelColor = m_levelTemplates [ _currentLevel ].getPixel( j, i );

			//ignore black pixels
 			if ( pixelColor == sf::Color::Black )
				continue;

			//get the hit point from the alpha channel. if max HP = 10, 10% opacity = 1 HP.
			int maxHp = MAX_HP == 0 ? 1 : abs( MAX_HP );// safety
			int hitPoint = ( int ) ( round( ( ( pixelColor.a / 255.f ) * 100.f ) / maxHp ) );

			//override the alpha because we don't need it anymore. We then get a full alpha color for the brick
			pixelColor.a = 255;

			//Create a new brick with the offset, size, pixel color and hit point
			m_bricks.emplace_back( std::make_shared<Game::Brick>( hitPoint, sf::Vector2f( _offset.x + j * _size.x, _offset.y + i * _size.y ), _size, pixelColor ) );
		}
	}
}

void Engine::OnBrickDestroyed( const Game::Brick& _brick )
{
	m_destroyedBrickCount++;
	
	PlaySound( Game::SoundName::BRICK_DESTROYED );

	SetScore( m_score +  50 ); //TODO: make score relative to the color of the brick destroyed.

	if ( m_destroyedBrickCount == m_bricks.size() )
	{
		LevelSucceeded();
	}
	else
	{
		//50% chance to spawn a random  power up
		if ( rand() % 2 != 0 )
		{
			m_powerUps.emplace_back( CreateRandomPowerUp( _brick.GetShape()->getPosition() ) );
		}
	}
}

bool Engine::IsCollidingWith( std::shared_ptr<Game::Shape> _shape1, std::shared_ptr<Game::Shape> _shape2 )
{
	if ( ( _shape1->GetRight() >= _shape2->GetLeft() && _shape1->GetLeft() <= _shape2->GetRight() &&
		 _shape1->GetBottom() >= _shape2->GetTop() && _shape1->GetTop() <= _shape2->GetBottom() ) )
	{
		//trigger collision for both shapes
		_shape2->OnCollision( _shape1 ); 
		_shape1->OnCollision( _shape2 );

		return true;
	}
	return false;
}

bool Engine::CanRemoveALife( int _ballIndex )
{
	//removes the ball from the list if we have more than one ball
	if ( m_balls.size() > 1 )
	{
		m_balls.erase( m_balls.begin() + _ballIndex );
		return false;
	}

	//Check game over
	if ( m_lifeSprites.size() == 0 )
	{
		GameOver();
		return false;
	}

	//remove a life
	m_lifeSprites.pop_back();
	PlaySound( Game::SoundName::LIFE_LOST );

	return true;
}

#pragma endregion

#pragma region Useful Methods

BallSharedPtr Engine::CreateBall( const  sf::Vector2f& _position, const  sf::Vector2f& _velocity, const sf::Color& _color )
{	
	return  std::shared_ptr<Game::Ball>( new Game::Ball( BALL_SPEED, _position, m_ballSize, GetSprite( SpriteType::BALL ), _color, _velocity ) );
}

PlayerRectangleSharedPtr Engine::CreatePlayer()
{
	return  std::shared_ptr<Game::PlayerRectangle>( new Game::PlayerRectangle( PLAYER_SPEED, m_playerPosition, m_playerSize, GetSprite( SpriteType::PLAYER ) ));
}

PowerSharedPtr Engine::CreateRandomPowerUp( const sf::Vector2f& _position )
{
	PowerUpType randomPowerUp = ( PowerUpType ) ( rand() % PowerUpType::POWER_UP_COUNT );
	return Game::PowerUp::Create( randomPowerUp, _position, m_brickSize, GetSprite( randomPowerUp ) );
}

void Engine::AddLife()
{
	sf::Sprite life = GetSprite( SpriteType::LIFE );
	life.setScale( .5f, .5f );
	life.setPosition( m_lifeSprites.size() * 40.f + 2.f, WINDOW_HEIGHT - 32.f );
	m_lifeSprites.emplace_back( life );
}

void Engine::FormatText( sf::Text & _text, const sf::String& _string, const sf::Font& _font, unsigned int _size, const sf::Vector2f& _position, const sf::Color &_fillColor )
{
	_text.setString( _string );
	_text.setFont( _font );
	_text.setCharacterSize( _size );
	_text.setPosition( _position );
	_text.setFillColor( _fillColor );
	_text.setOutlineColor( sf::Color::Black );
	_text.setOutlineThickness( 2 );
}

const sf::Sprite Engine::GetSprite( SpriteType _type )
{
	switch ( _type )
	{
		case PLAYER:
			return sf::Sprite( m_spriteSheet, sf::IntRect( 1158, 462, 243, 64 ) );
		case BALL:
			return sf::Sprite( m_spriteSheet, sf::IntRect( 1403, 652, 64, 64 ) );
		case LIFE:
			return 	sf::Sprite( m_spriteSheet, sf::IntRect( 1637, 652, 64, 58 ) );
		case BRICK:
			//TODO
			break;
		default:
			break;
	}

	return sf::Sprite();
}

const sf::Sprite Engine::GetSprite( PowerUpType _type )
{
	switch ( _type )
	{
		case PLAYER_SIZE_UP:
			return sf::Sprite( m_spriteSheet, sf::IntRect( 1158, 264, 243, 64 ) );
		case PLAYER_SIZE_DOWN:
			return sf::Sprite( m_spriteSheet, sf::IntRect( 1158, 198, 243, 64 ) );
		case MULTIPLE_BALLS:
			return sf::Sprite( m_spriteSheet, sf::IntRect( 594, 910, 243, 64 ) );
		case BALL_SPEED_UP:
			return sf::Sprite( m_spriteSheet, sf::IntRect( 349, 910, 243, 64 ) );
		case BALL_SPEED_DOWN:
			return sf::Sprite( m_spriteSheet, sf::IntRect( 1158, 66, 243, 64 ) );
		case SUPER_BALL:
			return sf::Sprite( m_spriteSheet, sf::IntRect( 1262, 726, 243, 64 ) );
		default:
			break;
	}

	return sf::Sprite();
}

#pragma endregion

#pragma region Power Ups

void Engine::ActivateSuperBall()
{
	//makes brick destructible in one hit
	for ( size_t i = m_bricks.size(); i--; )
	{
		if ( m_bricks [ i ]->isDestroyed() )
			continue;

		m_bricks [ i ]->SetHp( 1 );
	}

	//balls now don't bounce off bricks
	for ( size_t i = m_balls.size(); i--; )
	{
		m_balls [ i ]->SetIgnoreBrickReflection( true );
	}
}

void Engine::CreateDuplicateBall( const sf::Vector2f& _velocity )
{
	//Max 3 balls at once and at least one ball to copy
	if ( m_balls.size() >= 3 || m_balls.size() == 0 )
		return;

	sf::Vector2f position { m_balls [ 0 ]->GetShape()->getPosition() };
	m_balls.emplace_back( CreateBall( position, _velocity, sf::Color::Red ) );
}

void Engine::MultiplyBallsSpeed( float _multiplier )
{
	for ( size_t i = m_balls.size(); i--; )
	{
		m_balls [ i ]->MultiplySpeed( _multiplier );
	}
}

#pragma endregion




