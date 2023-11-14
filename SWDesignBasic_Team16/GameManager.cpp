#include "GameManager.h"

void GameManager::initWindow() {
	std::ifstream ifs("Config/window.ini");

	std::string title;
	sf::VideoMode windowBounds(1280, 720);
	unsigned int frameRateLimit = 60;
	bool verticalSyncEnabled = true;

	if (ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> windowBounds.width >> windowBounds.height;
		ifs >> frameRateLimit;
		ifs >> verticalSyncEnabled;
	}

	ifs.close();

	this->window = new sf::RenderWindow(windowBounds, title);
	this->window->setFramerateLimit(frameRateLimit);
	this->window->setVerticalSyncEnabled(verticalSyncEnabled);
}

void GameManager::initStates() {
	this->states.push(new GameState(this->window));
}

GameManager::GameManager() {
	this->initWindow();
	this->initStates();
}

GameManager::~GameManager() {
	delete this->window;

	while (!this->states.empty()) {
		delete this->states.top();
		this->states.pop();
	}
}

void GameManager::endGame() {
	std::cout << "Ending Game\n";
}

void GameManager::updateDt() {
	this->dt = this->dtClock.restart().asSeconds();
}

void GameManager::updateSFMLEvents() {
	while (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed)
			this->window->close();
	}
}

void GameManager::update() {
	this->updateSFMLEvents();

	if (!this->states.empty()) {
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit()) {
			this->states.top()->endState();

			delete this->states.top();
			this->states.pop();
		}
	}
	else {
		this->endGame();
		this->window->close();
	}
}

void GameManager::render() {
	this->window->clear();

	if (!this->states.empty())
		this->states.top()->render();

	this->window->display();
}

void GameManager::run() {
	while (this->window->isOpen()) {
		this->updateDt();
		this->update();
		this->render();
	}
}
