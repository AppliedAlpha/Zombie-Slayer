#pragma once
#include "Event.h"
class NPCEvent : public Event
{
private:
public:
	sf::RectangleShape textField;
	sf::Font font;
	NPCEvent(Player* player);
	~NPCEvent();
	void initScreen();
	void showSelectionScreen();
	void update(const float& dt);
	void render(sf::RenderTarget* target);
};

