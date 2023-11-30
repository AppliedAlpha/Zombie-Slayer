#pragma once

#include "stdafx.h"
#include "GameState.h"
#include "EventState.h"
#include "MainMenuState.h"
#include "GameOverState.h"

class GameManager
{
private:
	sf::RenderWindow* window;
	sf::Event event;

	sf::Clock dtClock;
	float dt;

	std::deque<State*> states;

	void initWindow();
	void initStates();

public:
	GameManager();
	virtual ~GameManager();

	void endGame();

	template <typename CurrentState, typename NextState>
	void transitionStates(bool autoTransit = false);

	void pushStates(std::deque<Event*>& eventQueue, sf::View& view);
	void updateDt();
	void updateSFMLEvents();
	void update();
	void render();
	void run();
};

