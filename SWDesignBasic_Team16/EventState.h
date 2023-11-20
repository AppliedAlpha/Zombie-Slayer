#pragma once
#include "State.h"
#include "Event.h"
class EventState : public State
{
private:
public:
	Event* event;
	int inputTerm = 0;
	EventState(sf::RenderWindow* window, Event* event);
	~EventState();
	void endState();
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target);
};

