#include "GameState.h"

void GameState::initStages()
{
	// adding stages to deque
	this->stages.push_back(new Stage(1));
	this->stages.push_back(new Stage(2));

	this->nowStage = this->stages.front();
	printf("[Stage %d]\n", this->nowStage->level);

	printf("%s\n", this->nowStage->mobList.front()->name.c_str());
}

GameState::GameState(sf::RenderWindow* window) : State(window) {
	this->ui = GameUI(sf::Vector2f(640, 360));


	this->window->setView(view);

	this->initStages();
	// this->initFirstStage();

	this->timeUntilItemCooldown = 1.f;

	this->npcList.push_back(new NPC());
	this->player.invincible = false;
	this->bombduration = 0.f;
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
	Mob* mob = this->nowStage->spawnMob();
	this->mobList.push_back(mob);
}

void GameState::spawnBoss() {
	Mob* boss = this->nowStage->spawnBoss();

	this->mobList.push_back(boss);
}

void GameState::endState() {
	std::cout << "Ending State\n";
}

void GameState::updateCollision(sf::Vector2f& velocity)
{
	sf::FloatRect playerNextPosBounds = this->player.shape.getGlobalBounds();
	sf::FloatRect bombBounds = this->player.bomb->shape.getGlobalBounds();
	for (auto weapon : this->player.weaponList) {
		MeleeWeapon* meleeWeapon = (MeleeWeapon*)weapon.second;
		sf::FloatRect meleeWeaponBounds = meleeWeapon->shape.getGlobalBounds();
		for (int i = 0; i < this->mobList.size(); i++) {
			sf::FloatRect mobBounds = mobList[i]->getShape().getGlobalBounds();
			if (mobBounds.intersects(meleeWeaponBounds) && meleeWeapon->active) {
				// printf("Collision\n");
				mobList[i]->updateCollision(meleeWeapon, this->player.power);
				if (mobList[i]->getDeath()) {
					// 
					DropItem* dropitem = new DropItem(mobList[i]->shape.getPosition(), mobList[i]->inventory);
					dropItemList.push_back(dropitem);
					xpList[i] = this->mobList[i]->getXP();
					goldList[i] = this->mobList[i]->getGold();
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
		if (mobBounds.intersects(bombBounds) && this->player.bomb->active) {
			// printf("Collision\n");
			mobList[i]->updateCollision(this->player.bomb);
			if (mobList[i]->getDeath()) {
				// 
				DropItem* dropitem = new DropItem(mobList[i]->shape.getPosition(), mobList[i]->inventory);
				dropItemList.push_back(dropitem);
				xpList[i] = this->mobList[i]->getXP();
				goldList[i] = this->mobList[i]->getGold();
				delete mobList[i];
				this->mobList.erase(this->mobList.begin() + i);
			}
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
			this->player.inventory.setXp(this->player.inventory.getXp() + xpList[i]);
			this->player.inventory.setGold(this->player.inventory.getGold() + goldList[i]);
			if (this->player.inventory.getXp() >= 20) {
				this->player.level = this->player.level + this->player.inventory.getXp() / 20;
				this->player.inventory.setXp(this->player.inventory.getXp() - 20);
				this->eventQueue.push_back(new OptionSelectionEvent(&this->player));
			}

			std::cout << "Level: " << this->player.level << ", Xp: " << this->player.inventory.getXp() << std::endl;
			std::cout << "Gold:  " << this->player.inventory.getGold() << std::endl;

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
			if (this->player.bomb->active == false) this->player.bomb->active = true;

			std::cout << "Item Used: No. " << i << '\n';
			this->timeUntilItemCooldown = 1.f;
		}
	}
}

void GameState::updateItemUse(const float& dt) {
	this->timeUntilItemCooldown -= dt;
	if (this->player.bomb->active == true) this->bombduration += dt;
	if (this->bombduration >= 0.3f) {
		this->player.bomb->active = false;
		bombduration = 0.f;
	}

	if (this->timeUntilItemCooldown <= 0)
		this->timeUntilItemCooldown = 0.f;

	// std::cout << this->itemCoolDownTime << '\n';
}

void GameState::updateMobSpawn(const float& dt) {
	if (this->nowStage->nextSpawnTime == 0.f && this->mobList.size() < this->nowStage->maxMobCount) {
		this->spawnMob();
	}

	if (!this->nowStage->isBossSpawned && this->nowStage->bossSpawnTime == 0.f) {
		this->spawnBoss();
	}
}

void GameState::updateStageClear()
{
	if (this->nowStage->isBossSpawned && this->mobList.empty()) {
		printf("Stage %d Clear\n", this->nowStage->level);

		this->stages.pop_front();
		
		if (this->stages.empty()) {
			this->quit = true;
			return;
		}
		this->nowStage = this->stages.front();
	}
}

void GameState::update(const float& dt) {
	this->updateInput(dt);
	this->updateCollision(this->velocity);
	this->player.update(dt, this->velocity);

	if (CustomMath::getLength(this->velocity) != 0.f) {
		this->view.move(this->player.movementSpeed * dt * 20 * this->velocity);
		this->window->setView(view);
	}

	this->ui.updateCenterPos(sf::Vector2f(this->player.cx, this->player.cy));
	this->ui.updateHpBar(this->player.hp, 100.f);
	this->ui.updateXpBar(this->player.inventory.getXp(), 20.f);

	this->updateItemUse(dt);

	this->nowStage->update(dt);
	this->updateMobSpawn(dt);

	for (auto mob : this->mobList) {
		mob->update(dt, sf::Vector2f(this->player.cx, this->player.cy));
	}

	for (auto npc : this->npcList) {
		npc->update(dt);
	}

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
		if (weapon.second->active) {
			weapon.second->render(target);
		}
	}

	if (this->player.bomb->active) {
		this->player.bomb->render(target);
	}
	
	this->ui.render(target);

	sf::Font font;
	font.loadFromFile("Arial.ttf");
	sf::Text goldText;
	sf::Text levelText;
	goldText.setFont(font);
	levelText.setFont(font);
	goldText.setCharacterSize(20);
	levelText.setCharacterSize(20);
	goldText.setFillColor(sf::Color::Yellow);
	levelText.setFillColor(sf::Color::White);
	goldText.setPosition(-620.f + this->player.cx, -340.f + this->player.cy);
	levelText.setPosition(-620.f + this->player.cx, -360.f + this->player.cy);
	goldText.setString("Gold: " + std::to_string(this->player.inventory.getGold()));
	levelText.setString("Level: " + std::to_string(this->player.level));

	target->draw(goldText);
	target->draw(levelText);
}