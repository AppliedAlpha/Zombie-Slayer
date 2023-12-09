#include "GameOverState.h"

GameOverState::GameOverState(sf::RenderWindow* window) : State(window) {
	this->font = new sf::Font();
	this->font->loadFromFile("./Resources/Arial.ttf");

	this->resultText = new sf::Text();

	this->bgTexture.loadFromFile("./Resources/GameOver.png");
	this->bgSprite.setTexture(bgTexture);
}

GameOverState::GameOverState(sf::RenderWindow* window, const bool& allClear, const double& playTime, const int& killCount, const double& totalDamage, const int& totalXp, const int& totalGold, std::unordered_map<int, Weapon*>* weaponList) : State(window) {
	this->font = new sf::Font();
	this->font->loadFromFile("./Resources/Arial.ttf");

	this->bgTexture.loadFromFile(allClear ? "./Resources/GameClear.png" : "./Resources/GameOver.png");
	this->bgSprite.setTexture(bgTexture);

	this->resultText = new sf::Text();
	this->resultText->setFont(*this->font);
	this->resultText->setCharacterSize(24);
	this->resultText->setFillColor(sf::Color::White);
	this->resultText->setPosition(sf::Vector2f(320, 210));

	char resTextBuffer[1001];

	int secTime = (int)(playTime * 10);
	int underSecTime = secTime % 10;
	secTime /= 10;

	std::sprintf(resTextBuffer, "Play Time: %02d:%02d.%01d\n\nTotal Kill Count: %d\nTotal Dealed Damage: %.0lf\nTotal Earned Xp: %d\nTotal Earned Gold: %d\n\n", secTime / 60, secTime % 60, underSecTime, killCount, totalDamage, totalXp, totalGold);

	auto beforeWeaponText = std::string(resTextBuffer);

	char weaponName[6][9] = {"Sword", "Spear", "Grinder", "Pistol", "Brick", "Rocket"};
	for (int i = 0; i < 6; i++) {
		if (weaponList->find(i) != weaponList->end()) {
			beforeWeaponText += "Level Of ";
			beforeWeaponText += weaponName[i];
			beforeWeaponText += ": ";
			beforeWeaponText += std::to_string(weaponList->at(i)->level);
			beforeWeaponText += '\n';
		}
	}
	this->resultText->setString(beforeWeaponText);
}

GameOverState::~GameOverState() {
	delete this->resultText;
	delete this->font;
}

void GameOverState::endState() {
	std::cout << "Exiting GameOver\n";
}

void GameOverState::updateInput(const float& dt) {
	this->checkForQuit();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && inputTerm >= 10) {
		this->inputTerm = 0;
		this->quit = true;
		this->exitCode = ExitCode::NEXT;
	}
}

void GameOverState::update(const float& dt) {
	if (inputTerm < 10) {
		inputTerm++;
	}

	this->updateInput(dt);
}

void GameOverState::render(sf::RenderTarget* target) {
	if (!target)
		target = this->window;

	target->draw(bgSprite);
	target->draw(*resultText);
}
