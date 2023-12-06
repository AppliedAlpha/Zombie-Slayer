#include "EventState.h"

EventState::EventState(sf::RenderWindow* window, sf::View& view, Event* event) : State(window, view)
{
	this->event = event;
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
		else if (StoreEvent* store = dynamic_cast<StoreEvent*>(this->event)) {
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && inputTerm >= 10) {
				store->index = store->index - 1 < 0 ? store->length - 1 : store->index - 1;
				store->update(dt);
				inputTerm = 0;
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && inputTerm >= 10) {
				store->index = store->index + 1 >= store->length ? 0 : store->index + 1;
				store->update(dt);
				inputTerm = 0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && inputTerm >= 10) {
				store->update(dt, store->options.at(store->index));
				inputTerm = 0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && inputTerm >= 10) {
				this->quit = true;
				inputTerm = 0;
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
