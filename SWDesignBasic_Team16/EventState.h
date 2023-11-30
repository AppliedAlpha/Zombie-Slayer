#pragma once

#include "State.h"
#include "NPCEvent.h"
#include "OptionSelectionEvent.h"

class EventState : public State
{
private:
public:
	Event* event;
	EventState(sf::RenderWindow* window, sf::View& view, Event* event);
	~EventState();
	void endState();
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target);
};

