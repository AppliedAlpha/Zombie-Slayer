#pragma once

#include "stdafx.h"
#include "Event.h"

enum ExitCode {
	DEFAULT = 0, ESC, NEXT
};

class State
{
private:

protected:
	sf::RenderWindow* window;

	std::vector<sf::Texture> textures;
	bool quit;
	ExitCode exitCode;

public:
	int inputTerm = 0;

	sf::View view;
	std::deque<Event*> eventQueue;
	State(sf::RenderWindow* window);
	State(sf::RenderWindow* window, sf::View& view);
	sf::Vector2f center;
	virtual ~State();

	const bool& getQuit() const;
	const ExitCode& getExitCode() const;
	virtual void checkForQuit();

	virtual void endState() = 0;
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

