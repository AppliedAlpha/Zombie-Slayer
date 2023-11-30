#include "Stage.h"

Stage::Stage(int level) : level(level) {
	switch (this->level) {
	case 1:
		enqueueMob(2, 2, "Normal Zombie", 3, 1, 40/*80*/, sf::Color::Green, 20, 2);
		enqueueMob(2, 2, "Fast Zombie", 5, 2, 35/*70*/, sf::Color::Magenta, 15, 2);
		enqueueMob(2, 2, "Helmet Zombie", 3, 3, 80/*80*/, sf::Color::Cyan, 25, 2);
		setBoss(100, 20, "Boss I", 2, 3, 100/*200*/, sf::Color::Blue, 50);

		initStageVariables(5, 15, 0.5f, 50.f);
		break;

	case 2:
		// TODO: NPC도 하나 추가해야 함
		enqueueMob(2, 2, "Normal Zombie", 3, 1, 40/*80*/, sf::Color::Green, 20, 15);
		enqueueMob(2, 2, "Fast Zombie", 5, 1, 35/*70*/, sf::Color(0, 127, 0, 255), 15, 10);
		setBoss(100, 20, "Boss II", 2, 3, 150/*300*/, sf::Color::Blue, 50);

		initStageVariables(7, 20, 2.5f, 50.f);
		break;
	}
}

Stage::~Stage() {
	// swap trick
	std::deque<Mob *>().swap(mobList);
}

void Stage::initStageVariables(int _maxMobCount, int _leftKillCountUntilBoss, float _mobSpawnTime, float _bossSpawnTime) {
	this->maxMobCount = _maxMobCount;
	this->leftKillCountUntilBoss = _leftKillCountUntilBoss;
	this->mobSpawnTime = _mobSpawnTime;
	this->bossSpawnTime = _bossSpawnTime;
	this->nextSpawnTime = this->mobSpawnTime;

	this->isBossSpawned = false;
	this->isClear = false;
}

void Stage::enqueueMob(int gold, int xp, const std::string& name, float movementSpeed, float power, float hp, const sf::Color& color, float size, int count) {
	while (count--)
		this->mobList.push_back(new Mob(gold, xp, name, movementSpeed, power, hp, color, size));
}

void Stage::setBoss(int gold, int xp, const std::string& name, float movementSpeed, float power, float hp, const sf::Color& color, float size) {
	// 나중에는 보스로 변경
	this->boss = new Mob(gold, xp, name, movementSpeed, power, hp, color, size);
}

Mob* Stage::spawnMob() {
	Mob* mob = this->mobList.front();
	this->mobList.pop_front();

	this->nextSpawnTime = this->mobSpawnTime;

	return mob;
}

Mob* Stage::spawnBoss() {
	if (!this->isBossSpawned) {
		this->isBossSpawned = true;
		return boss;
	}
}

void Stage::update(const float& dt) {
	this->updateSpawnTime(dt);
}

void Stage::updateSpawnTime(const float& dt) {
	if (!mobList.empty()) {
		this->nextSpawnTime -= dt;
		if (this->nextSpawnTime < 0.f)
			this->nextSpawnTime = 0.f;
	}

	if (!isBossSpawned) {
		this->bossSpawnTime -= dt;
		if (this->bossSpawnTime < 0.f)
			this->bossSpawnTime = 0.f;
	}
}
