#include "GameState.h"

void GameState::initStages()
{
	Stage stage1(1, 10);
	Stage stage2(2, 10);

	// 테스트용
	stage1.AddEncounter("Normal Zombie", 15);
	// stage1.AddEncounter("Hello Zombie", 10);

	// stage2.AddEncounter("Normal Zombie", 15);
	// stage2.AddEncounter("Hello Zombie", 15);

	// adding stages to vector
	this->stages.push_back(stage1);
	this->stages.push_back(stage2);

	// set first stage and index
	this->currentStageIndex = this->stages.begin();
	this->currentStage = *currentStageIndex;

	std::cout << this->currentStage.stageLevel << ' ' << this->currentStage.maxMobCount << '\n';

	this->currentStage.killCountUntilBoss = 10;
	this->currentStage.totalMobCount = 15;
	this->currentStage.bossSpawnTime = 30;
	this->currentStage.currentKillCount = 0;

	this->timeUntilSpawn = this->currentStage.nextSpawnTime;
	this->timeUntilBoss = this->currentStage.bossSpawnTime;

	for (int i = 0; i < 10; i++) {
		Mob* mob = new Mob();
		this->mobList.push_back(mob);
		this->currentStage.totalMobCount--;
	}
}

void GameState::initPlayerHpBar()
{
	hpBar[0] = sf::Vertex(sf::Vector2f(100.f, 50.f), sf::Color::Red);
	hpBar[1] = sf::Vertex(sf::Vector2f(100.f, 100.f), sf::Color::Red);
	hpBar[2] = sf::Vertex(sf::Vector2f(1180.f, 100.f), sf::Color::Red);
	hpBar[3] = sf::Vertex(sf::Vector2f(1180.f, 50.f), sf::Color::Red);
}

GameState::GameState(sf::RenderWindow* window) : State(window) {
	this->xp = 0;
	this->level = 0;

	this->initStages();
	// this->initFirstStage();
	this->initPlayerHpBar();
	this->timeUntilItemCooldown = 1.f;

	this->npcList.push_back(new NPC());
}

GameState::~GameState() {
	for (int i = 0; i < this->mobList.size(); i++) {
		delete this->mobList.at(i);
	}
	this->mobList.clear();

	for (int i = 0; i < this->npcList.size(); i++) {
		delete this->npcList.at(i);
	}
	this->npcList.clear();
}

void GameState::spawnMob()
{
	Mob* mob = new Mob();
	this->mobList.push_back(mob);
	this->currentStage.totalMobCount--;

	// 원래는 랜덤이거나 앞에 있어야 하는건데 일단
	/*
	std::string mobName = "Normal Zombie";
	
	this->currentStage.SubEncounter(mobName);
	this->mobs.push_back(mobName);
	*/
}

void GameState::spawnBoss() {
	Mob* boss = new Mob("Boss", 1.f, 3.f, 300.f);

	this->currentStage.isBossSpawned = true;
	this->mobList.push_back(boss);
}

void GameState::endState() {
	std::cout << "Ending State\n";
}

void GameState::updateCollision(sf::Vector2f& velocity)
{
	sf::FloatRect playerNextPosBounds = this->player.shape.getGlobalBounds();
	for (auto weapon : this->player.weaponList) {
		MeleeWeapon* meleeWeapon = (MeleeWeapon*)weapon;
		sf::FloatRect meleeWeaponBounds = meleeWeapon->shape.getGlobalBounds();
		for (int i = 0; i < this->mobList.size(); i++) {
			sf::FloatRect mobBounds = mobList[i]->getShape().getGlobalBounds();
			if (mobBounds.intersects(meleeWeaponBounds) && meleeWeapon->active) {
				// printf("Collision\n");
				mobList[i]->updateCollision(meleeWeapon);
				if (mobList[i]->getDeath()) {
					// 
					DropItem* dropitem = new DropItem(mobList[i]->shape.getPosition(), mobList[i]->inventory);
					dropItemList.push_back(dropitem);
					delete mobList[i];
					this->mobList.erase(this->mobList.begin() + i);
				}
			}
		}
	}
	for (int i = 0; i < this->mobList.size(); i++) {
		sf::FloatRect mobBounds = mobList[i]->getShape().getGlobalBounds();
		if (mobBounds.intersects(playerNextPosBounds)) {
			this->player.updateCollision(mobList[i]);
		}
	}
	for (int i = 0; i < this->npcList.size(); i++) {
		sf::FloatRect npcBounds = npcList[i]->getShape().getGlobalBounds();
		if (npcBounds.intersects(playerNextPosBounds)) {
			if (npcList[i]->active == false) {
				npcList[i]->active = true;
				this->eventQueue.push_back(new NPCEvent(&this->player));
			}
			delete npcList[i];
			this->npcList.erase(this->npcList.begin() + i);
		}
	}
	for (int i = 0; i < this->dropItemList.size(); i++) {
		sf::FloatRect dropItemBounds = dropItemList[i]->shape.getGlobalBounds();
		if (dropItemBounds.intersects(playerNextPosBounds)) {
			xp += 1;
			if (xp % 10 == 0) { 
				xp = 0; 
				level += 1;
			}
			std::cout << "Level: " << level << ", Xp: " << xp << std::endl;

			delete dropItemList[i];
			this->dropItemList.erase(this->dropItemList.begin() + i);
		}
	}
}

void GameState::updateInput(const float& dt) {
	this->checkForQuit();
	this->velocity.x = 0;
	this->velocity.y = 0;
	this->player.viewDirection.x = 0.f;
	this->player.viewDirection.y = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->player.viewDirection.x = -1.f;
		this->velocity.x = -1.f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->player.viewDirection.x = 1.f;
		this->velocity.x = 1.f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		this->player.viewDirection.y = -1.f;
		this->velocity.y = -1.f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
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
	if (!this->currentStage.isBossSpawned) {
		this->timeUntilBoss -= dt;

		if (this->timeUntilBoss <= 0) {
			this->spawnBoss();
			this->timeUntilBoss = 0;
		}
	}

	if (this->mobList.size() < this->currentStage.maxMobCount && this->currentStage.totalMobCount > 0) {
		this->timeUntilSpawn -= dt;

		if (this->timeUntilSpawn <= 0) {
			this->spawnMob();
			this->timeUntilSpawn = this->currentStage.nextSpawnTime;
		}
	}

	// std::cout << "Mob count: " << this->mobList.size() << ", until: " << this->timeUntilSpawn << ", boss until: " << this->timeUntilBoss << '\n';
	
}

void GameState::updateHpBar()
{
	hpBar[2] = sf::Vertex(sf::Vector2f(100.f + this->player.hp * 10.8, 100.f), sf::Color::Red);
	hpBar[3] = sf::Vertex(sf::Vector2f(100.f + this->player.hp * 10.8, 50.f), sf::Color::Red);
}

void GameState::updateStageClear()
{
	if (this->currentStage.isBossSpawned && this->mobList.empty()) {
		std::cout << "Stage 1 Clear" << std::endl;
		this->quit = true;
	}
}

void GameState::update(const float& dt) {
	this->updateInput(dt);
	this->updateCollision(this->velocity);
	this->player.update(dt, this->velocity);

	this->updateItemUse(dt);
	this->updateMobSpawn(dt);

	for (auto mob : this->mobList) {
		mob->update(dt, sf::Vector2f(this->player.cx, this->player.cy));
	}

	for (auto npc : this->npcList) {
		npc->update(dt);
	}

	this->updateHpBar();

	if (this->player.hp <= 0) {
		this->quit = true;
	}

	this->updateStageClear();
}

void GameState::render(sf::RenderTarget* target) {
	if (!target)
		target = this->window;
	
	// 맵 출력이 플레이어보다 앞서야 함
	this->basicMap.render(target);
	this->player.render(target);

	for (auto mob : this->mobList)
		mob->render(target);

	for (auto npc : this->npcList)
		npc->render(target);
	
	for (auto dropitem : this->dropItemList)
		dropitem->draw(target);
	
	for (auto weapon : this->player.weaponList) {
		if (weapon->active) {
			weapon->render(target);
		}
	}

	target->draw(hpBar, 4, sf::Quads);
}
