#include "Stage.h"

Stage::Stage(int level, std::map<std::string, sf::Sprite*>* mappedSprite) : level(level), mappedSprite(mappedSprite) {
	int totalCount = 100;
	int totalWave = 5;
	float waveTime = 5.f;
	int speed = 3;
	int power = 1;
	int hp = 200;
	int gold = 1;
	int xp = 2;
	float scale = 1.f;
	switch (this->level) {
	case 1:
		this->waveCount = 30;
		totalWave = 6;
		totalCount = this->waveCount * totalWave;
		waveTime = 5.f;
		setDialogArchive(this->level);
		setNPC("NPC I", 3, 1, 40, sf::Color::Yellow, 20);
		enqueueMob(gold, xp, "Normal Zombie", speed, power, hp, sf::Color::Green, 20/*size*/, totalCount, false, 0);
		//enqueueMob(1, 1, "Fast Zombie", 3.5, 1, 80, sf::Color(23, 10, 69, 255), 15, 10, false, 0);
		//enqueueMob(1, 1, "Helmet Zombie", 1, 2, 300, sf::Color(255, 127, 0, 255), 30, 10, false, 0);
		//enqueueMob(1, 1, "Shooting Zombie", 3, 1, 100, sf::Color(0, 63, 0, 255), 20, 10, true, 1);
		//enqueueMob(1, 1, "Brick Zombie", 1, 2, 300, sf::Color(245, 151, 0, 255), 30, 10, true, 2);
		shuffleMob();
		setBoss(gold * 100, xp * 50, "Boss I", speed, power * 3, hp * 5, sf::Color::Blue, 50 /*size*/, 1);
		initStageVariables(totalCount, totalCount - waveCount, waveTime, (totalCount - waveCount) / waveCount * waveTime);
		break;

	case 2:
		this->waveCount = 50;
		totalWave = 8;
		totalCount = this->waveCount * totalWave;
		waveTime = 5.f;
		scale = 1.25f;
		setDialogArchive(this->level);
		setNPC("NPC II", 3, 1, 40/*80*/, sf::Color::Yellow, 20);
		enqueueMob(gold, xp, "Normal Zombie", speed, power, hp * scale, sf::Color::Green, 20/*size*/, int(totalCount * 0.2), false, 0);
		enqueueMob(gold, xp, "Fast Zombie", speed * 2, power, hp * scale, sf::Color(0, 63, 0, 255), 15 /*size*/, totalCount - int(totalCount * 0.2), false, 0);
		shuffleMob();
		setBoss(gold * 120, xp * 60, "Boss II", speed + 1, power + 1, hp * 7.5 * scale, sf::Color::Blue, 50 /*size*/, 2);
		initStageVariables(totalCount, totalCount - waveCount, waveTime, (totalCount - waveCount) / waveCount * waveTime);
		break;

	case 3:
		this->waveCount = 75;
		totalWave = 10;
		totalCount = this->waveCount * totalWave;
		waveTime = 5.f;
		scale = 1.5f;
		setDialogArchive(this->level);
		setNPC("NPC III", 3, 1, 40/*80*/, sf::Color::Yellow, 20);
		enqueueMob(gold, xp, "Shooting Zombie", speed, power, hp * scale, sf::Color::Green, 20 /*size*/, int(totalCount * 0.05), true, 1);
		enqueueMob(gold, xp, "Normal Zombie", speed, power, hp * scale, sf::Color::Green, 20/*size*/, int(totalCount * 0.6), false, 0);
		enqueueMob(gold, xp, "Helmet Zombie", speed, power + 1, hp * 1.5 * scale, sf::Color(255,127,0,255), 30 /*size*/, totalCount - int(totalCount * 0.1) - int(totalCount * 0.6), false, 0);
		shuffleMob();
		setBoss(gold * 150, xp * 80, "Boss III", speed + 2, power + 2, hp * 10 * scale, sf::Color::Blue, 50/*size*/, 3);
		initStageVariables(totalCount, totalCount - waveCount, waveTime, (totalCount - waveCount) / waveCount * waveTime);
		break;

	case 4:
		this->waveCount = 100;
		totalWave = 12;
		totalCount = this->waveCount * totalWave;
		waveTime = 5.f;
		scale = 2.f;
		setDialogArchive(this->level);
		setNPC("NPC IV", 3, 1, 40/*80*/, sf::Color::Yellow, 20);
		enqueueMob(gold, xp, "Fast Zombie", speed * 2, power, hp * scale, sf::Color(0, 63, 0, 255), 15 /*size*/, int(totalCount * 0.5), false, 0);
		enqueueMob(gold, xp, "Helmet Zombie", speed, power + 1, hp * 1.5 * scale, sf::Color(255, 127, 0, 255), 30, totalCount - int(totalCount * 0.5) - int(totalCount * 0.05), false, 0);
		enqueueMob(gold, xp, "Brick Zombie", speed, power + 1, hp * 1.3 * scale, sf::Color(245, 151, 0, 255), 30, int(totalCount * 0.05), true, 2);
		shuffleMob();
		setBoss(gold * 200, xp * 100, "Boss IV", speed + 3, power + 3, hp * 12.5 * scale, sf::Color::Blue, 50, 4);
		initStageVariables(totalCount, totalCount - waveCount, waveTime, (totalCount - waveCount) / waveCount * waveTime);
		break;

	case 5:
		this->waveCount = 120;
		totalWave = 15;
		totalCount = this->waveCount * totalWave;
		waveTime = 5.f;
		scale = 3.f;
		setDialogArchive(this->level);
		setNPC("NPC IV", 3, 1, 40/*80*/, sf::Color::Yellow, 20);
		enqueueMob(gold, xp, "Normal Zombie", speed, power, hp * scale, sf::Color::Green, 20/*size*/, totalCount - int(totalCount * 0.05) - int(totalCount * 0.05) - int(totalCount * 0.2) - int(totalCount * 0.2), false, 0);
		enqueueMob(gold, xp, "Fast Zombie", speed * 2, power, hp * scale, sf::Color(0, 63, 0, 255), 15 /*size*/, int(totalCount * 0.2), false, 0);
		enqueueMob(gold, xp, "Helmet Zombie", speed, power + 1, hp * 1.5 * scale, sf::Color(255, 127, 0, 255), 30, int(totalCount * 0.2), false, 0);
		enqueueMob(gold, xp, "Shooting Zombie", speed, power, hp * scale, sf::Color::Green, 20 /*size*/, int(totalCount * 0.05), true, 1);
		enqueueMob(gold, xp, "Brick Zombie", speed, power + 1, hp * 1.3 * scale, sf::Color(245, 151, 0, 255), 30, int(totalCount * 0.05), true, 2);
		shuffleMob();
		setBoss(gold * 250, xp * 120, "Boss IV", speed + 4, power + 4, hp * 15 * scale, sf::Color::Blue, 50, 5);
		initStageVariables(totalCount, totalCount - waveCount, waveTime, (totalCount - waveCount) / waveCount * waveTime);
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
	this->nextSpawnTime = 0;

	this->isBossSpawned = false;
	this->isClear = false;
	this->isNPCSpawned = false;
}

void Stage::enqueueMob(int gold, int xp, const std::string& name, float movementSpeed, float power, float hp, const sf::Color& color, float size, int count, bool weapon, int weapontype) {
	sf::Sprite* sp_ptr = nullptr;
	if (this->mappedSprite->find(name) != this->mappedSprite->end())
		sp_ptr = this->mappedSprite->at(name);
	
	while (count--) {
		auto mob = new Mob(gold, xp, name, movementSpeed, power, hp, color, size, sp_ptr);
		if (weapon) {
			if (weapontype == 1) mob->weapon = new Pistol(1.5f, 5.f, 5.f, sf::Vector2f(mob->cx, mob->cy), 2.5, sf::Color(204, 204, 238));
			else if (weapontype == 2) mob->weapon = new Brick(3.f, 10.f, 7.f, sf::Vector2f(mob->cx, mob->cy), 1.5, sf::Color(204, 204, 238));
		}
		this->mobList.push_back(mob);
	}
}

void Stage::shuffleMob() {
	std::random_shuffle(this->mobList.begin(), this->mobList.end());
}

void Stage::setBoss(int gold, int xp, const std::string& name, float movementSpeed, float power, float hp, const sf::Color& color, float size, int weapontype) {
	// 나중에는 보스로 변경
	sf::Sprite* sp_ptr = nullptr;
	if (this->mappedSprite->find(name) != this->mappedSprite->end())
		sp_ptr = this->mappedSprite->at(name);
	this->boss = new Mob(gold, xp, name, movementSpeed, power, hp, color, size, sp_ptr);
	if (weapontype >= 1) {
		boss->weapon = new Grinder(0.f, 1.f, 0.f, sf::Vector2f(boss->cx, boss->cy),sf::Color(154,154,188));
		boss->weapon->shape.setScale(3, 3);
		Grinder* grinder = dynamic_cast<Grinder*>(boss->weapon);
		grinder->rotationSpeed = 2;
	}
	else if (weapontype == 2) {
		boss->weapon = new Pistol(3.f, 4.f, 7.f, sf::Vector2f(boss->cx, boss->cy), 2.5, sf::Color(154, 154, 188));
	}
	else if (weapontype == 3) {
		boss->weapon = new Pistol(3.f, 4.f, 7.f, sf::Vector2f(boss->cx, boss->cy), 2.5, sf::Color(154, 154, 188));
	}
}

void Stage::setNPC(const std::string& name, float movementSpeed, float power, float hp, const sf::Color& color, float size)
{
	delete this->npc;
	this->npc = new NPC(name, movementSpeed, power, hp, color, size);
}

Mob* Stage::spawnMob() {
	if (this->mobList.empty()) return nullptr;
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
	return nullptr;
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
		this->dialogArchive.first.push_back("I want to join with you.");
		this->dialogArchive.first.push_back("Here is a present for you.");
		this->dialogArchive.first.push_back("You got 10 golds.");

		this->dialogArchive.second.push_back("Oh, You are not Zombie!");
		this->dialogArchive.second.push_back("I want to join with you.");
		this->dialogArchive.second.push_back("Here is a present for you.");
		this->dialogArchive.second.push_back("You got 10 golds.");
		break;
	case 2:
		this->dialogArchive.first.push_back("Oh, You are not Zombie!");
		this->dialogArchive.first.push_back("I want to join with you.");
		this->dialogArchive.first.push_back("Here is a present for you.");
		this->dialogArchive.first.push_back("You got an Ice Item.");

		this->dialogArchive.second.push_back("You realized he is not a human.");
		this->dialogArchive.second.push_back("It's a Zombie!");
		this->dialogArchive.second.push_back("and you heard the sound of an explosion.");
		this->dialogArchive.second.push_back("BOOM!!");
		break;
	case 3:
		this->dialogArchive.first.push_back("Oh, You are not Zombie!");
		this->dialogArchive.first.push_back("I want to join with you.");
		this->dialogArchive.first.push_back("Here is a present for you.");
		this->dialogArchive.first.push_back("You got a Bomb item.");

		this->dialogArchive.second.push_back("You realized he is not a human.");
		this->dialogArchive.second.push_back("It's a Zombie!");
		this->dialogArchive.second.push_back("and you heard the sound of an explosion.");
		this->dialogArchive.second.push_back("BOOM!!");
		break;
	case 4:
		this->dialogArchive.first.push_back("Oh, You are not Zombie!");
		this->dialogArchive.first.push_back("I want to join with you.");
		this->dialogArchive.first.push_back("I can increase your level");
		this->dialogArchive.first.push_back("Level up!");

		this->dialogArchive.second.push_back("You realized he is not a human.");
		this->dialogArchive.second.push_back("It's a Zombie!");
		this->dialogArchive.second.push_back("and you heard the sound of an explosion.");
		this->dialogArchive.second.push_back("BOOM!!");
		break;
	case 5:
		this->dialogArchive.first.push_back("Oh, You are not Zombie!");
		this->dialogArchive.first.push_back("I want to join with you.");
		this->dialogArchive.first.push_back("Here is a present for you.");
		this->dialogArchive.first.push_back("You got an Ice item.");
		this->dialogArchive.first.push_back("You got a Bomb item.");
		this->dialogArchive.first.push_back("Level up!");

		this->dialogArchive.second.push_back("You realized he is not a human.");
		this->dialogArchive.second.push_back("It's a Zombie!");
		this->dialogArchive.second.push_back("and you heard the sound of an explosion.");
		this->dialogArchive.second.push_back("BOOM!!");
		break;
	default:
		break;
	}
}
