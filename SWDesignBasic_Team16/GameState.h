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
#include "MeleeWeapon.h"
#include "RangedWeapon.h"
#include "AoE.h"

class GameState : public State 
{
private:
	Player player;
	GameUI ui;
	std::vector<Mob*> mobList;
	int xpList[100];
	int goldList[100];
	std::vector<NPC*> npcList;
	sf::Vector2f velocity;
	Map basicMap;
	std::vector<DropItem*> dropItemList;
	std::vector<AoE*> aoeList;
	
	std::deque<Stage *> stages;
	Stage* nowStage;

	float timeUntilItemCooldown;
	float bombduration;
	// float timeUntilSpawn, timeUntilBoss;

	// int totalKillCount;
	// 이거 여기서 관리해줘도 되는건가?
	// Player한테 넘겨줘야 할 것 같다.

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

