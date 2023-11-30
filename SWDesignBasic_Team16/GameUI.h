#pragma once

#include "stdafx.h"

class GameUI
{
private:
	sf::Vector2f centerPos;
	sf::Vertex hpBar[4];
	sf::Vertex xpBar[4];

	sf::RectangleShape hpBackBar, xpBackBar;
	sf::Color red, blue, bottomRed, bottomBlue;
	sf::Color outlineGold;
	sf::IntRect hpBarRect, xpBarRect, timeTextRect;

	sf::Font* font;
	sf::Text levelText, goldText, timeText;
	char timeTextBuffer[13];

public:
	GameUI();
	GameUI(const sf::Vector2f& center, sf::Font* font);
	virtual ~GameUI();

	void initColors();
	void initRectPosValues();
	void initBars();
	void initTexts();

	void setBarPos(sf::Vertex* bar, const sf::IntRect& rect, const sf::Color& up, const sf::Color& down, const float fillPercent = 100.0f);

	void updateCenterPos(const sf::Vector2f& center);
	void updateHpBar(float hp, float maxHp);
	void updateXpBar(float xp, float maxXp);
	void updatePlayTimeText(float playTime);
	void updateLevelText(int level);
	void updateGoldText(int gold);

	void render(sf::RenderTarget* target);
};

