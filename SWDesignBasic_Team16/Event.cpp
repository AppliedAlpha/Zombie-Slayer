#include "Event.h"

Event::Event(Player* player)
{
	this->player = player;
	this->fontDir = "./Resources/Arial.ttf";
}

Event::~Event()
{
}

void Event::move(sf::Vector2f diff) {
	currentDialog.move(diff);
}
