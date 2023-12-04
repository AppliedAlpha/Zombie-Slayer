#pragma once

#include "stdafx.h"

class GameUI
{
private:
	sf::Texture* allTextures;
	sf::Sprite itemPotion;

	sf::Vector2f centerPos, diff;
	sf::Vertex hpBar[4];
	sf::Vertex xpBar[4];
	sf::Vertex itemSlotCoolBar[1][4];

	sf::RectangleShape hpBackBar, xpBackBar;
	sf::RectangleShape itemSlot[1];

	sf::Color red, blue, bottomRed, bottomBlue;
	sf::Color outlineGold, itemCoolBarColor;
	sf::IntRect hpBarRect, xpBarRect, itemSlotCoolBarRect;
	sf::Vector2f levelTextPos, goldTextPos, timeTextPos, stageTextPos;
	sf::Vector2f itemPotionCountTextPos;

	sf::Font* font;
	sf::Text levelText, goldText, timeText, stageText;
	sf::Text itemPotionCountText;

	char timeTextBuffer[13];

public:
	GameUI();
	GameUI(const sf::Vector2f& center, sf::Font* font, sf::Texture* texture);
	virtual ~GameUI();

	void initColors();
	void initRectPosValues();
	void initBars();
	void initTexts();

	void setBarPos(sf::Vertex* bar, const sf::IntRect& rect, const sf::Color& up, const sf::Color& down, const float fillPercent = 100.0f);

	void updateCenterPos(const sf::Vector2f& center);
	void updateHpBar(float hp, float maxHp);
	void updateXpBar(float xp, float maxXp);
	void updateItemSlot(float coolDown, int potionCount);
	void updatePlayTimeText(float playTime);
	void updateLevelText(int level);
	void updateGoldText(int gold);
	void updateStageText(int stage);

	void render(sf::RenderTarget* target);
};

