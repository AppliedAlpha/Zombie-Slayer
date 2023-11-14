#pragma once

#include "State.h"
#include "Entity.h"
#include "Stage.h"
#include "Map.h"

class GameState : public State
{
private:
	Entity player;
	Map basicMap;

	// 현재 깔려있는 몹
	// 원래는 Mob 클래스가 들어가야 함
	std::vector<std::string> mobs; 
	
	std::vector<Stage> stages;
	std::vector<Stage>::const_iterator currentStageIndex;
	Stage currentStage;


	float timeUntilItemCooldown;
	float timeUntilSpawn, timeUntilBoss;
	
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

	void updateInput(const float& dt);
	void updateItemUse(const float& dt);
	void updateMobSpawn(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

