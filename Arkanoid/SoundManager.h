#pragma once
#include <SFML/Audio.hpp>


namespace Game
{
	enum SoundName
	{
		BALL_COLLISION,
		BRICK_DESTROYED,
		LIFE_LOST, //TODO: LIFE GAIN
		POWER_UP,
		GAME_OVER,
		GAME_START,
		LEVEL_SUCCEEDED
	};
	class SoundManager
	{
		//Note: SFML needs the sounds and buffer to stay alive in order to play. Therefore we need to have the sounds and the buffer created
	private:

		sf::SoundBuffer m_ballCollisionBuffer;
		sf::SoundBuffer m_brickDestroyedBuffer;
		sf::SoundBuffer m_lifeLostBuffer;
		sf::SoundBuffer m_powerUpBuffer;
		sf::SoundBuffer m_gameOverBuffer;
		sf::SoundBuffer m_gameStartBuffer;
		sf::SoundBuffer m_levelSucceededBuffer;

		//create a pool  of 3 sounds to handle multiple sounds playing at the same time.
		//we should make an expandable pooler, but 4 sounds is enough to  handle 90% of all the cases of this simple game.
		//Its a good TODO.
		std::vector<sf::Sound> m_sounds { sf::Sound(),sf::Sound(),sf::Sound() , sf::Sound()};

		const sf::SoundBuffer& GetBuffer( SoundName _soundName );

	public:
		SoundManager();
		~SoundManager(){};

		void PlaySound( SoundName _soundName );
	};
}
