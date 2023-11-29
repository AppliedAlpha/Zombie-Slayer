#include "State.h"

State::State(sf::RenderWindow* window) {
	this->window = window;
	this->quit = false;
	this->exitCode = ExitCode::DEFAULT;
	this->center = sf::Vector2f(640.f, 360.f);
	this->view.setCenter(sf::Vector2f(640.f, 360.f));
	this->view.setSize(sf::Vector2f(1280.f, 720.f));
	this->window->setView(this->view);
}

State::State(sf::RenderWindow* window, sf::View& view) {
	this->center = sf::Vector2f(640.f, 360.f);
	this->window = window;
	this->quit = false;
	this->exitCode = ExitCode::DEFAULT;
	this->view = view;
}

State::~State() {
}

const bool& State::getQuit() const {
	return this->quit;
}

const ExitCode& State::getExitCode() const {
	return this->exitCode;
}

void State::checkForQuit() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && inputTerm >= 10) {
		this->quit = true;
		this->exitCode = ExitCode::ESC;
		this->inputTerm = 0;
	}
}