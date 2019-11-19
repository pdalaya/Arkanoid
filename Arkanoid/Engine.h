#pragma once

///////////////////////////////////////////////////////////////// Includes
#include <SFML/Graphics.hpp>
#include "PlayerRectangle.h"
#include "Brick.h"
#include "Ball.h"
#include "PowerUp.h"
#include "SoundManager.h"

///////////////////////////////////////////////////////////////// Defines (tweak able variables)
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define INITIAL_LIFE_COUNT 2
#define PLAYER_SPEED 600
#define BALL_SPEED 380
#define LEVEL_AMOUNT 3
#define MAX_HP 10
#define BALL_SPEED_SLOWDOWN_FACTOR .7f //between 0 and 1

///////////////////////////////////////////////////////////////// Typedef
typedef std::shared_ptr<Game::Brick> BrickSharedPtr;
typedef std::shared_ptr<Game::PlayerRectangle> PlayerRectangleSharedPtr;
typedef std::shared_ptr<Game::Ball> BallSharedPtr;
typedef std::shared_ptr<Game::PowerUp> PowerSharedPtr;

///////////////////////////////////////////////////////////////// Enum
//Game state
enum State
{
	LEVEL_START,
	MAIN,
	LEVEL_SUCCEEDED,
	GAME_OVER
};

//Different sprites
enum SpriteType
{
	PLAYER,
	BALL,
	LIFE,
	BRICK, //TODO
};

///////////////////////////////////////////////////////////////// Class Engine
class Engine
{
	///////////////////////////////////////////////////////////////// Private
private:
	static Engine* m_instance;
	Engine( int _widht, int _height );
	Engine( const Engine& );
	Engine& operator=( const Engine& );

	sf::RenderWindow m_window;
	Game::SoundManager m_soundManager; //sounds are loaded in the constructor

	//Assets
	sf::Sprite m_backgroundSprite;
	sf::Texture m_backgroundTexture;
	sf::Texture m_lifeTexture;
	std::vector<sf::Sprite> m_lifeSprites;
	std::vector<sf::Image> m_levelTemplates;
	sf::Texture m_spriteSheet;

	//Text
	sf::Font m_font;
	sf::Text m_gameOverText;
	sf::Text m_restartText;
	sf::Text m_startText;
	sf::Text m_levelText;
	sf::Text m_levelSucceededText;
	sf::Text m_keyBindingsText;
	sf::Text m_scoreLabelText;
	sf::Text m_scoreValueText;

	//Objects
	std::vector< BallSharedPtr > m_balls;
	PlayerRectangleSharedPtr m_playerRectangle;
	std::vector<BrickSharedPtr> m_bricks;
	std::vector<PowerSharedPtr> m_powerUps;

	//Useful
	sf::Vector2f m_playerSize;
	sf::Vector2f m_playerPosition;
	sf::Vector2f m_ballSize;
	sf::Vector2f m_ballPosition;
	sf::Vector2f m_brickSize;

	//Setter
	void SetScore( unsigned int _newScore )
	{
		m_score = _newScore;
		m_scoreValueText.setString( std::to_string(m_score) );
	}

	//Logic
	State m_state;
	bool m_keyPressed; //needed to process input properly.
	bool m_firstLevelSucceeded; //flag to display keybindings or not
	unsigned int m_currentLevel; 
	unsigned int m_destroyedBrickCount; //count that keeps the number of bricks destroyed. Needed to know if we suceeded a level .
	int m_score;

	///METHODS

	//Game Flow
	//reset and initializes components
	void SetupLevel(); 

	//called to notify that the level is succeeded
	void LevelSucceeded(); 

	void ChangeLevel( int _newLevel ); 

	//restart the level, or the game depending on the argument
	void RestartLevel( bool _restartGame = false ); 

	//called to notify game over
	void GameOver(); 

	//Places bricks according to a texture. Reads pixels from the texture and use color and opacity to creates corresponding bricks.
	void SetUpBricks( int _currentLevel, const sf::Vector2f& _offset, const sf::Vector2f& _size ); 

	//Called on a brick destruction. Needs the brick because sometimes we can spawn a Power up on the brick location
	void OnBrickDestroyed( const Game::Brick& _brick );

	//Basic collision detection AABB. 
	bool IsCollidingWith( std::shared_ptr<Game::Shape> _shape1, std::shared_ptr<Game::Shape> _shape2 );

	//Useful Methods
	BallSharedPtr CreateBall( const  sf::Vector2f& _position, const  sf::Vector2f& _velocity = sf::Vector2f( 0, 0 ), const sf::Color& _color = sf::Color::White);
	PlayerRectangleSharedPtr CreatePlayer();
	PowerSharedPtr CreateRandomPowerUp( const sf::Vector2f& _size );
	void AddLife();
	const sf::Sprite GetSprite( SpriteType _type );
	const sf::Sprite GetSprite( PowerUpType _type );

	//Pass in a text, formats using the arguments.
	void FormatText( sf::Text & _text, const sf::String& _string, const sf::Font& _font, unsigned int _size, const sf::Vector2f& _position, const sf::Color &_fillColor = sf::Color::White );

	//Engine tick

	//Gets inputs
	void ProcessInputs( float _deltaTime );

	//Update the collision and the movement
	void Update( float _deltaTime );

	//Rendering
	void Draw();

	///////////////////////////////////////////////////////////////// Public
public:

	~Engine(){
		delete m_instance;
	};

	//Singleton... Would normally use events or delegates instead of having a singleton. 
	static Engine* GetInstance()
	{
		if ( m_instance == nullptr )
		{
			m_instance = new Engine( WINDOW_WIDTH, WINDOW_HEIGHT );
		}

		return m_instance;
	}

	//First method called
	void Run();
	
	//Power ups 

	//makes the ball pass through bricks and destroy them in one hit !
	void ActivateSuperBall();

	//Creates 2 new balls 
	void CreateDuplicateBall( const sf::Vector2f& _velocity );

	//modify the speed of the balls
	void MultiplyBallsSpeed( float _multiplier );

	//Game Flow

	//called when a ball goes off screen. Only removes a life if the ball leaving the screen is the last one.
	bool CanRemoveALife( int _ballIndex ); 

	//Asks the sound manager to take care of playing the sound
	void PlaySound( Game::SoundName _soundName )
	{
		m_soundManager.PlaySound( _soundName );
	}

};



