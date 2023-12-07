#pragma once
#include "Event.h"
class StoreEvent : public Event
{
private:
public:
	sf::Texture bgTexture;
	sf::Sprite bgSprite;
	int index = 0;
	int length = 4;
	std::vector<std::string> options;
	std::vector<sf::RectangleShape*> optionFields;
	std::vector<sf::Text*> optionTexts;
	sf::Text title;
	sf::Text subtitle;
	sf::Text goldText;
	sf::Text script;
	sf::Font font;
	StoreEvent(Player* player);
	~StoreEvent();
	void initScreen();
	void showSelectionScreen();
	void update(const float& dt);
	void update(const float& dt, std::string option);
	void render(sf::RenderTarget* target);
	void move(sf::Vector2f diff);
};

