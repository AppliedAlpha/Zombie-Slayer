#include "EventState.h"

EventState::EventState(sf::RenderWindow* window, Event* event) : State(window)
{
	this->event = event;
}

EventState::~EventState()
{
	delete event;
}

void EventState::endState()
{
}

void EventState::updateInput(const float& dt)
{
}

void EventState::update(const float& dt)
{
	if (inputTerm < 10) {
		inputTerm++;
	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && inputTerm >= 10) {
			if (event->dialog.empty()) this->quit = true;
			else {
				event->update(dt);
			}
			inputTerm = 0;
		}
	}
}

void EventState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->event->render(target);
}
