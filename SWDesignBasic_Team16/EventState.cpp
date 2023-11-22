#include "EventState.h"

EventState::EventState(sf::RenderWindow* window, sf::View& view, Event* event) : State(window, view)
{
	this->event = event;
	std::cout << this->center.x - view.getCenter().x << " " << this->center.y - view.getCenter().y << std::endl;
	this->event->move(view.getCenter() - this->center);
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
		if (NPCEvent* npc = dynamic_cast<NPCEvent*>(this->event)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && inputTerm >= 10) {
				if (npc->dialog.empty()) this->quit = true;
				else {
					npc->update(dt);
				}
				inputTerm = 0;
			}
		}
		else if (OptionSelectionEvent* option = dynamic_cast<OptionSelectionEvent*>(this->event)) {
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && inputTerm >= 10) {
				option->index = option->index - 1 < 0 ? option->length - 1 : option->index - 1;
				option->update(dt);
				inputTerm = 0;
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && inputTerm >= 10) {
				option->index = option->index + 1 >= option->length ? 0 : option->index + 1;
				option->update(dt);
				inputTerm = 0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && inputTerm >= 10) {
				std::cout << "You Select " << option->options.at(option->index) << std::endl;
				option->update(dt, option->options.at(option->index));
				this->quit = true;
			}
		}
	}
}

void EventState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->event->render(target);
}
