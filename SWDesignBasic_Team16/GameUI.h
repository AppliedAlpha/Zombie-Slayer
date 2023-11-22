#pragma once

#include "stdafx.h"

class GameUI
{
private:
	sf::Vector2f centerPos;
	sf::Vertex hpBar[4];
	sf::Vertex xpBar[4];

public:
	GameUI();
	GameUI(const sf::Vector2f& center);
	virtual ~GameUI();

	void updateCenterPos(const sf::Vector2f& center);
	void updateHpBar(float hp, float maxHp);
	void updateXpBar(float xp, float maxXp);
	void render(sf::RenderTarget* target);
};

