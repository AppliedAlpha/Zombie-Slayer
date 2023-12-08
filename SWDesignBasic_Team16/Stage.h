#pragma once
#include "stdafx.h"
#include "Mob.h"
#include "Brick.h"
#include "Pistol.h"
#include "Sword.h"
#include "Grinder.h"
#include "Bomb.h"
#include "NPC.h"
// #include "Boss.h"  // ���� ���� ��� ������ �߰��ȴٸ� Mob ��ſ� �̰ŷ� ���� ���

class Stage
{
private:
	void initStageVariables(int _maxMobCount, int _leftKillCountUntilBoss, float _mobSpawnTime, float _bossSpawnTime);
	//void enqueueMob(int gold, int xp, const std::string& name, float movementSpeed, float power, float hp, const sf::Color& color, float size, int count, bool weapon = false);
	void shuffleMob();
	void setBoss(int gold, int xp, const std::string& name, float movementSpeed, float power, float hp, const sf::Color& color, float size, int weapontype);
	void setNPC(const std::string& name, float movementSpeed, float power, float hp, const sf::Color& color, float size);

public:
	void enqueueMob(int gold, int xp, const std::string& name, float movementSpeed, float power, float hp, const sf::Color& color, float size, int count, bool weapon, int weapontype);
	int level, maxMobCount;
	int leftKillCountUntilBoss;
	float nextSpawnTime, mobSpawnTime, bossSpawnTime;
	int waveCount;
	std::deque<Mob *> mobList;
	Mob *boss;
	bool isBossSpawned, isClear;
	bool isNPCSpawned;
	NPC* npc;
	std::map<std::string, sf::Sprite*>* mappedSprite;
	std::pair<std::deque<std::string>, std::deque<std::string>> dialogArchive;

	Stage(int level, std::map<std::string, sf::Sprite*>* mappedSprite);
	virtual ~Stage();

	Mob* spawnMob();
	Mob* spawnBoss();
	NPC* spawnNPC();
	
	void update(const float& dt);
	void updateSpawnTime(const float& dt);

	void setDialogArchive(int level);
};

