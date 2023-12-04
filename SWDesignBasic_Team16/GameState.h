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
#include "Random.h"

class GameState : public State
{
private:
	Player player;
	GameUI ui;
	sf::Font* font;
	bool allClear = false;

	std::vector<Mob*> mobList;

	//int* xpList = new int;
	//int* goldList = new int;
	std::vector<int> xpList;
	std::vector<int> goldList;

	std::vector<NPC*> npcList;
	sf::Vector2f velocity;
	Map backgroundMap;
	std::vector<AoE*> aoeList;
	int npcEvent = -1;
	sf::Vector2f npcEventPos;
	
	std::deque<Stage*> stages;
	std::vector<DropItem*> dropGoldList;
	std::vector<DropItem*> dropXpList;
	std::vector<DropItem*> dropBombList;
	std::vector<DropItem*> dropPotionList;
	Stage* nowStage;

	float timeUntilItemCooldown;
	float bombduration;
	float playTime = 0.f;

	sf::Texture* allTextures;
	std::map<std::string, sf::Sprite *>* mappedSprite;

	void initStages();

public:
	GameState(sf::RenderWindow* window);
	virtual ~GameState();

	void spawnMob();
	void spawnBoss();
	void spawnNPC();
	void endState();

	void updateNPCEvent(const float& dt);
	void updateCollision(sf::Vector2f& velocity);
	void updateInput(const float& dt);
	void updateItemUse(const float& dt);
	void updateMobSpawn(const float& dt);
	void updateStageClear();
	void update(const float& dt);
	void render(sf::RenderTarget* target);
};

