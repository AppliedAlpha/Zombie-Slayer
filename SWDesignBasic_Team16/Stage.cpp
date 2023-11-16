#include "Stage.h"

Stage::Stage()
{
}

Stage::Stage(int stageLevel, int maxMobCount) : stageLevel(stageLevel), maxMobCount(maxMobCount), killCountUntilBoss(maxMobCount * 3 / 4), nextSpawnTime(3.f), bossSpawnTime(90.f), isBossSpawned(false)
{
}

Stage::Stage(int stageLevel, int maxMobCount, int killCountUntilBoss, float nextSpawnTime, float bossSpawnTime) : stageLevel(stageLevel), maxMobCount(maxMobCount), killCountUntilBoss(killCountUntilBoss), nextSpawnTime(nextSpawnTime), bossSpawnTime(bossSpawnTime), isBossSpawned(false)
{
}

Stage::~Stage()
{
	// swap trick
	std::map<std::string, int>().swap(encounterList);
}

void Stage::AddEncounter(std::string name, int count)
{
	encounterList[name] += count;
}

void Stage::SubEncounter(std::string name)
{
	encounterList[name]--;

	if (encounterList[name] == 0)
		this->RemoveEncounter(name);
}

void Stage::RemoveEncounter(std::string name)
{
	if (encounterList.find(name) != encounterList.end()) {
		encounterList.erase(name);
	}
}
