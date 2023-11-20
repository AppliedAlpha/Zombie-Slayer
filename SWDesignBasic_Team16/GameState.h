#pragma once

#include "stdafx.h"
#include "State.h"
#include "Player.h"
#include "Mob.h"
#include "Stage.h"
#include "Map.h"
#include "NPC.h"

class GameState : public State
{
private:
	Player player;
	std::vector<Mob*> mobList;
	std::vector<NPC*> npcList;
	sf::Vector2f velocity;
	Map basicMap;
	std::vector<DropItem*> dropItemList;

	sf::Vertex hpBar[4];
	
	std::vector<Stage> stages;
	std::vector<Stage>::const_iterator currentStageIndex;
	Stage currentStage;

	int xp;
	int level;


	float timeUntilItemCooldown;
	float timeUntilSpawn, timeUntilBoss;
	
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

