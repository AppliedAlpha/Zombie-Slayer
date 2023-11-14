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

	// ���� ����ִ� ��
	// ������ Mob Ŭ������ ���� ��
	std::vector<std::string> mobs; 
	
	std::vector<Stage> stages;
	std::vector<Stage>::const_iterator currentStageIndex;
	Stage currentStage;


	float timeUntilItemCooldown;
	float timeUntilSpawn, timeUntilBoss;
	
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

	void updateInput(const float& dt);
	void updateItemUse(const float& dt);
	void updateMobSpawn(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

