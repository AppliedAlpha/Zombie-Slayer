#include "GameState.h"

void GameState::initStages()
{
	Stage stage1(1, 5);
	Stage stage2(2, 10);

	// 테스트용
	stage1.AddEncounter("Normal Zombie", 10);
	stage1.AddEncounter("Hello Zombie", 10);

	stage2.AddEncounter("Normal Zombie", 15);
	stage2.AddEncounter("Hello Zombie", 15);

	// adding stages to vector
	this->stages.push_back(stage1);
	this->stages.push_back(stage2);

	// set first stage and index
	this->currentStageIndex = this->stages.begin();
	this->currentStage = *currentStageIndex;

	std::cout << this->currentStage.stageLevel << ' ' << this->currentStage.maxMobCount << '\n';

	this->timeUntilSpawn = this->currentStage.nextSpawnTime;
	this->timeUntilBoss = this->currentStage.bossSpawnTime;
}

GameState::GameState(sf::RenderWindow* window) : State(window) {
	this->initStages();

	this->timeUntilItemCooldown = 1.f;
}

GameState::~GameState() {
}

void GameState::spawnMob()
{
	// 원래는 랜덤이거나 앞에 있어야 하는건데 일단
	std::string mobName = "Normal Zombie";
	
	this->currentStage.SubEncounter(mobName);
	this->mobs.push_back(mobName);
}

void GameState::spawnBoss() {
	std::string bossName = this->currentStage.boss;

	this->currentStage.isBossSpawned = true;
	this->mobs.push_back(bossName);
}

void GameState::endState() {
	std::cout << "Ending State\n";
}

void GameState::updateInput(const float& dt) {
	this->checkForQuit();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->player.move(dt, -1.f, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->player.move(dt, 1.f, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		this->player.move(dt, 0.f, -1.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		this->player.move(dt, 0.f, 1.f);
	}

	for (auto i = 1; i <= 9; i++) {
		if (this->timeUntilItemCooldown < 0.01f && sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(sf::Keyboard::Num1 - 1 + i))) {
			// this->player.useItem(i);
			std::cout << "Item Used: No. " << i << '\n';
			this->timeUntilItemCooldown = 1.f;
		}
	}
}

void GameState::updateItemUse(const float& dt) {
	this->timeUntilItemCooldown -= dt;

	if (this->timeUntilItemCooldown <= 0)
		this->timeUntilItemCooldown = 0.f;

	// std::cout << this->itemCoolDownTime << '\n';
}

void GameState::updateMobSpawn(const float& dt) {
	if (!this->currentStage.isBossSpawned) {
		this->timeUntilBoss -= dt;

		if (this->timeUntilBoss <= 0) {
			this->spawnBoss();
			this->timeUntilBoss = 0;
		}
	}

	if (this->mobs.size() < this->currentStage.maxMobCount) {
		this->timeUntilSpawn -= dt;

		if (this->timeUntilSpawn <= 0) {
			this->spawnMob();
			this->timeUntilSpawn = this->currentStage.nextSpawnTime;
		}
	}

	std::cout << "Mob count: " << this->mobs.size() << ", until: " << this->timeUntilSpawn << ", boss until: " << this->timeUntilBoss << '\n';
}

void GameState::update(const float& dt) {
	this->updateInput(dt);
	this->player.update(dt);

	this->updateItemUse(dt);
	this->updateMobSpawn(dt);
}

void GameState::render(sf::RenderTarget* target) {
	if (!target)
		target = this->window;
	
	// 맵 출력이 플레이어보다 앞서야 함
	this->basicMap.render(target);
	this->player.render(target);
}
