#include "GameOverState.h"

GameOverState::GameOverState(sf::RenderWindow* window) : State(window) {
	this->font = new sf::Font();
	this->font->loadFromFile("./Resources/Arial.ttf");

	this->bgTexture.loadFromFile("./Resources/GameOver.png");
	this->bgSprite.setTexture(bgTexture);
}

GameOverState::~GameOverState() {
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
}
