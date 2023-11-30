#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window) : State(window) {
	this->font = new sf::Font();
	this->font->loadFromFile("./Resources/Arial.ttf");

	this->bgTexture.loadFromFile("./Resources/Title.png");
	this->bgSprite.setTexture(bgTexture);
}

MainMenuState::~MainMenuState() {
	delete this->font;
}

void MainMenuState::endState() {
	std::cout << "Exiting MainMenu\n";
}

void MainMenuState::updateInput(const float& dt) {
	this->checkForQuit();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && inputTerm >= 10) {
		this->inputTerm = 0;
		this->quit = true;
		this->exitCode = ExitCode::NEXT;
	}
}

void MainMenuState::update(const float& dt) {
	if (inputTerm < 10) {
		inputTerm++;
	}

	this->updateInput(dt);
}

void MainMenuState::render(sf::RenderTarget* target) {
	if (!target)
		target = this->window;

	target->draw(bgSprite);
}
