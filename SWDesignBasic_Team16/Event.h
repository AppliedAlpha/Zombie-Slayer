#pragma once

#include "stdafx.h"
#include "Player.h"

class Event
{
private:
public:
	Player* player;
	std::deque<std::string> dialog;
	sf::Text currentDialog;
	std::string fontDir;
	sf::Font font;
	Event(Player* player);
	virtual ~Event();
	virtual void initScreen() = 0;
	virtual void showSelectionScreen() = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target) = 0;
};

