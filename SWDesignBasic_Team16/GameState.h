#pragma once

#include "stdafx.h"
#include "Player.h"
#include "Mob.h"
#include "Stage.h"
#include "Map.h"
#include "NPC.h"
#include "State.h"
#include "NPCEvent.h"
#include "OptionSelectionEvent.h"
#include "GameUI.h"

class GameState : public State 
{
private:
	Player player;
	GameUI ui;
	std::vector<Mob*> mobList;
	std::vector<NPC*> npcList;
	sf::Vector2f velocity;
	Map basicMap;
	std::vector<DropItem*> dropItemList;
	
	std::deque<Stage *> stages;
	Stage* nowStage;

	int xp;
	int level;

	float timeUntilItemCooldown;
	
	// int totalKillCount;
	// �̰� ���⼭ �������൵ �Ǵ°ǰ�?
	// Player���� �Ѱ���� �� �� ����.

	void initStages();

public:
	GameState(sf::RenderWindow* window);
	virtual ~GameState();

	void spawnMob();
	void spawnBoss();
	void endState();

	void updateCollision(sf::Vector2f& velocity);
	void updateInput(const float& dt);
	void updateItemUse(const float& dt);
	void updateMobSpawn(const float& dt);
	void updateStageClear();
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

