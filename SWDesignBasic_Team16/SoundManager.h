#pragma once
#include <SFML/Audio.hpp>

class SoundManager
{
private:
	SoundManager();
	~SoundManager();

	static SoundManager* _instance;

public:
	static SoundManager& instance() {
		if (_instance == nullptr) {
			_instance = new SoundManager();
		}

		return *_instance;
	}

	void load(sf::Sound* sound, sf::SoundBuffer* buffer, std::string file);

	sf::Music bgm;

	sf::Sound levelUp, stageClear, gameClear, gameOver, magnet;
	sf::Sound npc[2];
	sf::Sound itemUse[3];

	sf::SoundBuffer levelUpBuffer, stageClearBuffer, gameClearBuffer, gameOverBuffer, magnetBuffer;
	sf::SoundBuffer npcBuffer[2];
	sf::SoundBuffer itemUseBuffer[3];
};
