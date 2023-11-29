#include "Stage.h"

Stage::Stage(int level) : level(level) {
	switch (this->level) {
	case 1:
		setDialogArchive(this->level);
		setNPC("Survivor", 3, 1, 40/*80*/, sf::Color::Yellow, 20);
		enqueueMob(2, 20, "Normal Zombie", 3, 1, 40/*80*/, sf::Color::Green, 20, 20, true);
		setBoss(100, 20, "Boss I", 2, 3, 100/*200*/, sf::Color::Blue, 50);
		initStageVariables(5, 15, 0.5f, 50.f);
		break;

	case 2:
		// TODO: NPC도 
		// 하나 추가해야 함
		setDialogArchive(this->level);
		setNPC("NPC II", 3, 1, 40/*80*/, sf::Color::Yellow, 20);
		enqueueMob(2, 20, "Normal Zombie", 3, 1, 40/*80*/, sf::Color::Green, 20, 15, false);
		enqueueMob(2, 20, "Fast Zombie", 5, 0.75, 35/*70*/, sf::Color(0, 127, 0, 255), 15, 10, false);
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
	this->isNPCSpawned = false;
}

void Stage::enqueueMob(int gold, int xp, const std::string& name, float movementSpeed, float power, float hp, const sf::Color& color, float size, int count, bool weapon) {
	while (count--) {
		auto mob = new Mob(gold, xp, name, movementSpeed, power, hp, color, size);
		if (weapon)
			mob->weapon = new Pistol(3.f, 2.f, 2.f, sf::Vector2f(mob->cx, mob->cy), 5, sf::Color(128, 0, 128));
		this->mobList.push_back(mob);
	}
}

void Stage::setBoss(int gold, int xp, const std::string& name, float movementSpeed, float power, float hp, const sf::Color& color, float size) {
	// 나중에는 보스로 변경
	this->boss = new Mob(gold, xp, name, movementSpeed, power, hp, color, size);
}

void Stage::setNPC(const std::string& name, float movementSpeed, float power, float hp, const sf::Color& color, float size)
{
	delete this->npc;
	this->npc = new NPC(name, movementSpeed, power, hp, color, size);
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

NPC* Stage::spawnNPC()
{
	return this->npc;
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

void Stage::setDialogArchive(int level)
{
	this->dialogArchive.first.clear();
	this->dialogArchive.second.clear();
	switch (level)
	{
	case 1:
		this->dialogArchive.first.push_back("Oh, You are not Zombie!");
		this->dialogArchive.first.push_back("Survive here if you can.");
		this->dialogArchive.first.push_back("I have a present for you. Good Luck!");
		this->dialogArchive.first.push_back("You got 10 golds.");

		this->dialogArchive.second.push_back("Oh, Hi! You are not Zombie.");
		this->dialogArchive.second.push_back("Survive here if you can.");
		this->dialogArchive.second.push_back("I have a present for you. Good Luck!");
		this->dialogArchive.second.push_back("You got 10 golds.");
		break;
	case 2:
		this->dialogArchive.first.push_back("Oh, You are not Zombie!");
		this->dialogArchive.first.push_back("Survive here if you can.");
		this->dialogArchive.first.push_back("I have a present for you. Good Luck!");
		this->dialogArchive.first.push_back("You got 10 golds.");

		this->dialogArchive.second.push_back("Hello, You are not Zombie!");
		this->dialogArchive.second.push_back("Survive here if you can.");
		this->dialogArchive.second.push_back("I have a present for you. Good Luck!");
		this->dialogArchive.second.push_back("You got 10 golds.");
		break;
	case 3:
		this->dialogArchive.first.push_back("Oh, You are not Zombie!");
		this->dialogArchive.first.push_back("Survive here if you can.");
		this->dialogArchive.first.push_back("I have a present for you. Good Luck!");
		this->dialogArchive.first.push_back("You got 10 golds.");

		this->dialogArchive.second.push_back("Hello, You are not Zombie!");
		this->dialogArchive.second.push_back("Survive here if you can.");
		this->dialogArchive.second.push_back("I have a present for you. Good Luck!");
		this->dialogArchive.second.push_back("You got 10 golds.");
		break;
	case 4:
		this->dialogArchive.first.push_back("Oh, You are not Zombie!");
		this->dialogArchive.first.push_back("Survive here if you can.");
		this->dialogArchive.first.push_back("I have a present for you. Good Luck!");
		this->dialogArchive.first.push_back("You got 10 golds.");

		this->dialogArchive.second.push_back("Hello, You are not Zombie!");
		this->dialogArchive.second.push_back("Survive here if you can.");
		this->dialogArchive.second.push_back("I have a present for you. Good Luck!");
		this->dialogArchive.second.push_back("You got 10 golds.");
		break;
	case 5:
		this->dialogArchive.first.push_back("Oh, You are not Zombie!");
		this->dialogArchive.first.push_back("Survive here if you can.");
		this->dialogArchive.first.push_back("I have a present for you. Good Luck!");
		this->dialogArchive.first.push_back("You got 10 golds.");

		this->dialogArchive.second.push_back("Hello, You are not Zombie!");
		this->dialogArchive.second.push_back("Survive here if you can.");
		this->dialogArchive.second.push_back("I have a present for you. Good Luck!");
		this->dialogArchive.second.push_back("You got 10 golds.");
		break;
	case 6:
		this->dialogArchive.first.push_back("Oh, You are not Zombie!");
		this->dialogArchive.first.push_back("Survive here if you can.");
		this->dialogArchive.first.push_back("I have a present for you. Good Luck!");
		this->dialogArchive.first.push_back("You got 10 golds.");

		this->dialogArchive.second.push_back("Hello, You are not Zombie!");
		this->dialogArchive.second.push_back("Survive here if you can.");
		this->dialogArchive.second.push_back("I have a present for you. Good Luck!");
		this->dialogArchive.second.push_back("You got 10 golds.");
		break;
	default:
		break;
	}
}
