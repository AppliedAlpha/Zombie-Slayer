#include "SoundManager.h"
#include <iostream>

SoundManager* SoundManager::_instance = nullptr;

SoundManager::SoundManager() {
	if (!this->bgm.openFromFile("./Resources/Start.wav")) {
		std::cout << "No Music!" << std::endl;
	}

	this->bgm.setLoop(true);

	load(&levelUp, &levelUpBuffer, "./Resources/LevelUp.wav");
	load(&stageClear, &stageClearBuffer, "./Resources/StageClear.wav");
	load(&gameClear, &gameClearBuffer, "./Resources/GameClear.wav");
	load(&gameOver, &gameOverBuffer, "./Resources/GameOver.wav");
	load(&npc[0], &npcBuffer[0], "./Resources/npcNegative.wav");
	load(&npc[1], &npcBuffer[1], "./Resources/npcPositive.wav");
	load(&itemUse[0], &itemUseBuffer[0], "./Resources/Swallow.wav");
	load(&itemUse[1], &itemUseBuffer[1], "./Resources/Bomb.wav");
	load(&itemUse[2], &itemUseBuffer[2], "./Resources/Freeze.wav");
	load(&magnet, &magnetBuffer, "./Resources/Magnet.wav");
}

SoundManager::~SoundManager() {}

void SoundManager::load(sf::Sound* sound, sf::SoundBuffer* buffer, std::string file) {
	if (!buffer->loadFromFile(file)) {
		std::cout << "No Sound: " << file << std::endl;
	}

	sound->setBuffer(*buffer);
	sound->setLoop(false);
}
