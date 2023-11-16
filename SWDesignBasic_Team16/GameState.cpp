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

	for (int i = 0; i < 10; i++) {
		Mob* mob = new Mob();
		this->mobList.push_back(mob);
	}
}

GameState::GameState(sf::RenderWindow* window) : State(window) {
	this->initStages();

	this->timeUntilItemCooldown = 1.f;
}

GameState::~GameState() {
	for (int i = 0; i < this->mobList.size(); i++) {
		delete this->mobList.at(i);
	}
	this->mobList.clear();
}

void GameState::spawnMob()
{
	// 원래는 랜덤이거나 앞에 있어야 하는건데 일단
	/*
	std::string mobName = "Normal Zombie";
	
	this->currentStage.SubEncounter(mobName);
	this->mobs.push_back(mobName);
	*/
}

void GameState::spawnBoss() {
	std::string bossName = this->currentStage.boss;

	this->currentStage.isBossSpawned = true;
	// this->mobs.push_back(bossName);
}

void GameState::endState() {
	std::cout << "Ending State\n";
}

void GameState::updateCollision(sf::Vector2f& velocity)
{
	for (int i = 0; i < this->mobList.size(); i++) {
		sf::FloatRect playerNextPosBounds = this->player.shape.getGlobalBounds();
		sf::FloatRect mobBounds = mobList[i]->getShape().getGlobalBounds();
		sf::FloatRect swordBounds = this->player.sword->shape.getGlobalBounds();
		if (mobBounds.intersects(playerNextPosBounds)) {
			this->player.updateCollision(mobList[i], velocity);
		}
		if (mobBounds.intersects(swordBounds) && this->player.sword->active) {
			// printf("Collision\n");
			mobList[i]->updateCollision(this->player.sword);
			if (mobList[i]->hp <= 0) {
				delete mobList[i];
				this->mobList.erase(this->mobList.begin() + i);
			}
		}
	}
}

void GameState::updateInput(const float& dt, int& keyTime) {
	this->checkForQuit();
	this->velocity.x = 0;
	this->velocity.y = 0;
	this->player.viewDirection.x = 0.f;
	this->player.viewDirection.y = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		keyTime = 0;
		this->player.viewDirection.x = -1.f;
		this->velocity.x = -1.f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		keyTime = 0;
		this->player.viewDirection.x = 1.f;
		this->velocity.x = 1.f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		keyTime = 0;
		this->player.viewDirection.y = -1.f;
		this->velocity.y = -1.f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		keyTime = 0;
		this->player.viewDirection.y = 1.f;
		this->velocity.y = 1.f;
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
	/*
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
	*/
}

void GameState::update(const float& dt, int& keyTime) {
	if (keyTime < 4)
		keyTime++;
	
	this->updateInput(dt, keyTime);
	this->updateCollision(this->velocity);
	this->player.update(dt, this->velocity);

	this->updateItemUse(dt);
	this->updateMobSpawn(dt);

	for (auto mob : this->mobList) {
		mob->update(dt);
	}
}

void GameState::render(sf::RenderTarget* target) {
	if (!target)
		target = this->window;
	
	// 맵 출력이 플레이어보다 앞서야 함
	this->basicMap.render(target);
	this->player.render(target);

	for (auto mob : this->mobList)
		mob->render(target);
	
	if (this->player.sword->active) {
		this->player.sword->render(target);
	}
}
