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
#include "StoreEvent.h"
#include "GameUI.h"
#include "MeleeWeapon.h"
#include "RangedWeapon.h"
#include "AoE.h"
#include "Random.h"

class GameState : public State
{
private:
	GameUI ui;
	sf::Font* font;

	std::vector<Mob*> mobList;
	std::vector<Mob*> mobSpeedList;

	std::vector<int> xpList;
	std::vector<int> goldList;
	std::vector<NPC*> npcList;

	sf::RectangleShape border;
	sf::Vector2f velocity;
	Map backgroundMap;
	std::vector<AoE*> aoeList;
	int npcEvent = -1;
	sf::Vector2f npcEventPos;
	
	std::deque<Stage*> stages;
	std::vector<DropItem*> dropGoldList;
	std::vector<DropItem*> dropXpList;
	std::vector<DropItem*> dropBombList;
	std::vector<DropItem*> dropIceList;
	std::vector<DropItem*> dropPotionList;
	std::vector<DropItem*> dropMagneticList;
	Stage* nowStage;

	float timeUntilItemCooldown[3];

	sf::Texture* allTextures;
	std::map<std::string, sf::Sprite *>* mappedSprite;

	void initStages();

public:
	Player player;

	bool allClear = false;
	float playTime = 0.f;
	int totalKillCount = 0, totalXp = 0, totalGold = 0;
	double totalDamage = 0.f;

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

