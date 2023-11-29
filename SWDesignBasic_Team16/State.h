#pragma once

#include "stdafx.h"
#include "Event.h"

class State
{
private:

protected:
	sf::RenderWindow* window;

	std::vector<sf::Texture> textures;
	bool quit;

public:
	sf::View view;
	std::deque<Event*> eventQueue;
	State(sf::RenderWindow* window);
	State(sf::RenderWindow* window, sf::View& view);
	sf::Vector2f center;
	virtual ~State();

	const bool& getQuit() const;
	virtual void checkForQuit();

	virtual void endState() = 0;
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target) = 0;
};

