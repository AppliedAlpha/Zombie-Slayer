#pragma once
#include "stdafx.h"

class Stage
{
private:
	std::map<std::string, int> encounterList;

public:
	int stageLevel;
	int maxMobCount;
	int killCountUntilBoss;

	float nextSpawnTime;
	float bossSpawnTime;

	Stage();

	Stage(int stageLevel, int maxMobCount);

	Stage(int stageLevel, int maxMobCount, int killCountUntilBoss, float nextSpawnTime, float bossSpawnTime);
	virtual ~Stage();

	void AddEncounter(std::string name, int count);
	void SubEncounter(std::string name);
	void RemoveEncounter(std::string name);
};

