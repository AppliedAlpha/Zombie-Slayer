#pragma once
#include "Event.h"
#include "Player.h"

class NPCEvent : public Event
{
private:
public:
	sf::Texture bgTexture;
	sf::Sprite bgSprite;
	sf::RectangleShape textField;
	std::deque<std::string>& dialog;
	sf::Text currentDialog;
	sf::Text title;
	sf::Text subtitle;
	sf::Font font;
	int level;
	int& npcEvent;
	int positive;
	NPCEvent(Player* player, int level, std::deque<std::string>& dialog, std::string npc, int& npcEvent, int positive);
	~NPCEvent();
	void initScreen();
	void showSelectionScreen();
	void update(const float& dt);
	void render(sf::RenderTarget* target);
	void move(sf::Vector2f diff);
};

