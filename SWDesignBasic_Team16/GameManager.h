#pragma once

#include "stdafx.h"
#include "GameState.h"
#include "EventState.h"

class GameManager
{
private:
	sf::RenderWindow* window;
	sf::Event event;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	void initWindow();
	void initStates();

public:
	GameManager();
	virtual ~GameManager();

	void endGame();

	void pushStates(std::deque<Event*>& eventQueue, sf::View& view);
	void updateDt();
	void updateSFMLEvents();
	void update();
	void render();
	void run();
};

