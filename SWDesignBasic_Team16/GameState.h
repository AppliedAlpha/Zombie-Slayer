#pragma once

#include "stdafx.h"
#include "State.h"
#include "Player.h"
#include "Mob.h"
#include "Stage.h"
#include "Map.h"
#include "GameUI.h"

class GameState : public State 
{
private:
	Player player;
	GameUI ui;
	std::vector<Mob*> mobList;
	sf::Vector2f velocity;
	Map basicMap;
	std::vector<DropItem*> dropItemList;
	
	std::deque<Stage *> stages;
	Stage* nowStage;
	sf::View view;

	int xp;
	int level;

	float timeUntilItemCooldown;
	
	// int totalKillCount;
	// 이거 여기서 관리해줘도 되는건가?
	// Player한테 넘겨줘야 할 것 같다.

	void initStages();
	void initPlayerHpBar();

public:
	GameState(sf::RenderWindow* window);
	virtual ~GameState();

	void spawnMob();
	void spawnBoss();
	void endState();

	void updateCollision(sf::Vector2f& velocity);
	void updateInput(const float& dt, int& keyTime);
	void updateItemUse(const float& dt);
	void updateMobSpawn(const float& dt);
	void updateHpBar();
	void updateStageClear();
	void update(const float& dt, int& keyTime);
	void render(sf::RenderTarget* target = nullptr);
};

