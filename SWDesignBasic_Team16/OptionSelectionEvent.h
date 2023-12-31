#pragma once

#include "Event.h"
#include "stdafx.h"

class OptionSelectionEvent : public Event
{
private:
public:
	sf::Texture bgTexture;
	sf::Sprite bgSprite;
	int index = 0;
	int length = 3;
	std::vector<std::string> options;
	std::vector<sf::RectangleShape*> optionFields;
	std::vector<sf::Text*> optionTexts;
	sf::Text script;
	sf::String newWeapon = "New: ";
	sf::String upgradeWeapon = "Upgrade: ";
	sf::Text title;
	sf::Text subtitle;
	sf::Font font;
	OptionSelectionEvent(Player* player);
	~OptionSelectionEvent();
	void initScreen();
	void showSelectionScreen();
	void update(const float& dt);
	void update(const float& dt, std::string option);
	void render(sf::RenderTarget* target);
	void move(sf::Vector2f diff);
	void selectRandomWeapon();
};

