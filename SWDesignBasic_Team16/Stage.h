#pragma once
#include "stdafx.h"
#include "Mob.h"
#include "Pistol.h"
#include "NPC.h"
// #include "Boss.h"  // 만약 보스 헤더 파일이 추가된다면 Mob 대신에 이거로 수정 요망

class Stage
{
private:
	void initStageVariables(int _maxMobCount, int _leftKillCountUntilBoss, float _mobSpawnTime, float _bossSpawnTime);
	void enqueueMob(int gold, int xp, const std::string& name, float movementSpeed, float power, float hp, const sf::Color& color, float size, int count, bool weapon = false);
	void setBoss(int gold, int xp, const std::string& name, float movementSpeed, float power, float hp, const sf::Color& color, float size);
	void setNPC(const std::string& name, float movementSpeed, float power, float hp, const sf::Color& color, float size);

public:
	int level, maxMobCount;
	int leftKillCountUntilBoss;
	float nextSpawnTime, mobSpawnTime, bossSpawnTime;

	std::deque<Mob *> mobList;
	Mob *boss;
	bool isBossSpawned, isClear;
	bool isNPCSpawned;
	NPC* npc;
	std::pair<std::deque<std::string>, std::deque<std::string>> dialogArchive;

	Stage(int level);
	virtual ~Stage();

	Mob* spawnMob();
	Mob* spawnBoss();
	NPC* spawnNPC();
	
	void update(const float& dt);
	void updateSpawnTime(const float& dt);

	void setDialogArchive(int level);
};

