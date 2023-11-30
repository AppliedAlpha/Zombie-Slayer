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
	this->font = new sf::Font();
	this->font->loadFromFile("./Resources/Arial.ttf");

	this->allTextures = new sf::Texture();
	this->allTextures->loadFromFile("./Resources/Textures.png");

	this->mappedSprite["Normal Zombie"] = new sf::Sprite(*this->allTextures, sf::IntRect(0, 0, 20, 20));

	this->ui = GameUI(sf::Vector2f(640, 360), this->font);

	this->window->setView(view);

	this->initStages();
	// this->initFirstStage();

	this->timeUntilItemCooldown = 1.f;
	this->player.invincible = false;
	this->bombduration = 0.f;
}

GameState::~GameState() {
	// swap trick
	std::vector<Mob *>().swap(this->mobList);
	std::vector<NPC *>().swap(this->npcList);
	std::vector<AoE *>().swap(this->aoeList);
	std::map<std::string, sf::Sprite*>().swap(this->mappedSprite);

	delete this->allTextures;
	delete this->font;
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

void GameState::spawnNPC()
{
	this->nowStage->isNPCSpawned = true;
	NPC* npc = this->nowStage->spawnNPC();
	npc->cx = npc->cx + this->player.cx;
	npc->cy = npc->cy + this->player.cy;
	npc->shape.setPosition(npc->cx, npc->cy);
	this->npcList.push_back(npc);
}

void GameState::endState() {
	std::cout << "Ending State\n";
}

void GameState::updateCollision(sf::Vector2f& velocity)
{
	sf::FloatRect playerNextPosBounds = this->player.shape.getGlobalBounds();
	sf::FloatRect bombBounds = this->player.bomb->shape.getGlobalBounds();
	for (auto weapon : this->player.weaponList) {
		if (MeleeWeapon* melee = dynamic_cast<MeleeWeapon*>(weapon.second)) {
			sf::FloatRect weaponBounds = melee->shape.getGlobalBounds();
			for (int i = 0; i < this->mobList.size(); i++) {
				sf::FloatRect mobBounds = mobList[i]->getShape().getGlobalBounds();
				if (mobBounds.intersects(weaponBounds) && melee->active) {
					// printf("Collision\n");
					mobList[i]->updateCollision(melee, this->player.power);
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
		else if (RangedWeapon* ranged = dynamic_cast<RangedWeapon*>(weapon.second)) {
			for (auto bullet : ranged->bullets) {
				sf::FloatRect bulletBounds = bullet->shape.getGlobalBounds();
				for (int i = 0; i < this->mobList.size(); i++) {
					sf::FloatRect mobBounds = mobList[i]->getShape().getGlobalBounds();
					if (mobBounds.intersects(bulletBounds)) {
						mobList[i]->updateCollision(ranged, this->player.power);
						if (bullet->maxHitCount <= bullet->hitCount) {
							if (bullet->explosion) {
								this->aoeList.push_back(bullet->explode(ranged->radius, ranged->explosionDuration, ranged->explosionDamage, mobList[i]->shape.getPosition()));
							}
							bullet->out = true;
						}
						if (mobList[i]->getDeath()) {
							DropItem* dropitem = new DropItem(mobList[i]->shape.getPosition(), mobList[i]->inventory);
							dropItemList.push_back(dropitem);
							xpList[i] = this->mobList[i]->getXP();
							goldList[i] = this->mobList[i]->getGold();
							delete mobList[i];
							this->mobList.erase(this->mobList.begin() + i);
						}
						else bullet->hitCount++;
					}
				}
			}
		}
	}

	for (auto aoe : this->aoeList) {
		sf::FloatRect aoeBounds = aoe->shape.getGlobalBounds();
		if (aoe->mobTarget) {
			for (int i = 0; i < this->mobList.size(); i++) {
				sf::FloatRect mobBounds = mobList[i]->getShape().getGlobalBounds();
				if (mobBounds.intersects(aoeBounds)) {
					// printf("Collision\n");
					mobList[i]->updateCollision(aoe);
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
		else {
			if (playerNextPosBounds.intersects(aoeBounds)) {
				this->player.updateCollision(aoe);
			}
		}
	}

	for (int i = 0; i < this->mobList.size(); i++) {
		if (mobList[i]->weapon != nullptr) {
			if (RangedWeapon* ranged = dynamic_cast<RangedWeapon*>(mobList[i]->weapon)) {
				for (auto bullet : ranged->bullets) {
					sf::FloatRect bulletBounds = bullet->shape.getGlobalBounds();
					if (playerNextPosBounds.intersects(bulletBounds)) {
						this->player.updateCollision(ranged);
						if (bullet->explosion) {
							this->aoeList.push_back(bullet->explode(ranged->radius, ranged->explosionDuration, ranged->explosionDamage, mobList[i]->shape.getPosition()));
						}
						bullet->out = true;
					}
				}
			}
		}
		sf::FloatRect mobBounds = mobList[i]->getShape().getGlobalBounds();
		if (mobBounds.intersects(playerNextPosBounds)) {
			this->player.updateCollision(mobList[i]);
		}
		if (mobBounds.intersects(bombBounds) && this->player.bomb->active) {
			mobList[i]->updateCollision(this->player.bomb);
			if (mobList[i]->getDeath()) {
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
				if (npcList[i]->positive == 1) {
					this->eventQueue.push_back(new NPCEvent(&this->player, this->nowStage->level, this->nowStage->dialogArchive.first, npcList[i]->name, this->npcEvent, this->npcList[i]->positive));
				}
				else {
					this->eventQueue.push_back(new NPCEvent(&this->player, this->nowStage->level, this->nowStage->dialogArchive.second, npcList[i]->name, this->npcEvent, this->npcList[i]->positive));
				}
				this->npcEventPos = sf::Vector2f(this->npcList[i]->cx, this->npcList[i]->cy);
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

			int lastMaxXp = CustomMath::getMaxXp(this->player.level);

			while (this->player.inventory.getXp() >= lastMaxXp) {
				this->player.level++;
				this->player.inventory.setXp(this->player.inventory.getXp() - lastMaxXp);
				lastMaxXp = CustomMath::getMaxXp(this->player.level);

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

	if (!this->nowStage->isNPCSpawned) {
		this->spawnNPC();
	}
}

void GameState::updateNPCEvent(const float& dt) {
	if (this->npcEvent) {
		switch (this->nowStage->level)
		{
		case 1:
			this->player.inventory.setGold(this->player.inventory.getGold() + 10);
		case 2:
			this->aoeList.push_back(new AoE(200, .5f, 1.f, this->npcEventPos));
		case 3:
			this->player.movementSpeed = this->player.movementSpeed + 10;
		case 4:
			this->mobList.push_back(new Mob(2, 2, std::string("Normal Zombie"), 3.f, 1.f, 40.f/*80*/, sf::Color::Green, 20.f));
			this->mobList.at(this->mobList.size() - 1)->cx = this->npcEventPos.x;
			this->mobList.at(this->mobList.size() - 1)->cy = this->npcEventPos.y;
			this->mobList.at(this->mobList.size() - 1)->shape.setPosition(this->npcEventPos);
		case 5:

		case 6:

		default:
			break;
		}
	}
	else {
		switch (this->nowStage->level)
		{
		case 1:
			this->player.inventory.setGold(this->player.inventory.getGold() + 10);
		case 2:
			this->aoeList.push_back(new AoE(200, .5f, 1.f, this->npcEventPos, false));
		case 3:
			this->player.movementSpeed = this->player.movementSpeed - 10;
		case 4:
			this->mobList.push_back(new Mob(2, 2, std::string("Normal Zombie"), 3.f, 1.f, 40.f/*80*/, sf::Color::Green, 20.f));
			this->mobList.at(this->mobList.size() - 1)->cx = this->npcEventPos.x;
			this->mobList.at(this->mobList.size() - 1)->cy = this->npcEventPos.y;
			this->mobList.at(this->mobList.size() - 1)->shape.setPosition(this->npcEventPos);
		case 5:

		case 6:
			break;
		default:
			break;
		}
	}
	this->npcEvent = -1;
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
	if (inputTerm < 10) {
		inputTerm++;
	}

	this->updateInput(dt);
	this->updateCollision(this->velocity);
	this->player.update(dt, this->velocity);

	if (CustomMath::getLength(this->velocity) != 0.f) {
		this->velocity = CustomMath::normalize(this->velocity);
		this->view.move(this->player.movementSpeed * dt * this->velocity);
		this->window->setView(view);
	}

	this->updateItemUse(dt);

	this->nowStage->update(dt);
	this->updateMobSpawn(dt);

	for (int i = 0; i < aoeList.size(); i++) {
		aoeList[i]->update(dt);
		if (aoeList[i]->disappear) {
			delete aoeList[i];
			aoeList.erase(aoeList.begin() + i);
		}
	}

	for (auto mob : this->mobList) {
		mob->update(dt, sf::Vector2f(this->player.cx, this->player.cy));
	}

	if (this->npcEvent != -1) {
		this->updateNPCEvent(dt);
	}

	for (auto npc : this->npcList) {
		npc->update(dt);
	}

	if (this->player.hp <= 0) {
		this->quit = true;
	}

	this->playTime += dt;

	// ui update
	this->ui.updateCenterPos(sf::Vector2f(this->player.cx, this->player.cy));
	this->ui.updateHpBar(this->player.hp, 100.f);
	this->ui.updateXpBar(this->player.inventory.getXp(), CustomMath::getMaxXp(this->player.level));
	this->ui.updateLevelText(this->player.level);
	this->ui.updateGoldText(this->player.inventory.getGold());
	this->ui.updatePlayTimeText(this->playTime);

	this->updateStageClear();
}

void GameState::render(sf::RenderTarget* target) {
	// 맵 출력이 플레이어보다 앞서야 함
	this->basicMap.render(target);

	for (auto npc : this->npcList)
		npc->render(target);
	
	for (auto dropitem : this->dropItemList)
		dropitem->draw(target);
	
	for (auto weapon : this->player.weaponList) {
		if (MeleeWeapon* melee = dynamic_cast<MeleeWeapon*>(weapon.second)) {
			if (melee->active)
				melee->render(target);
		}
		else if (RangedWeapon* ranged = dynamic_cast<RangedWeapon*>(weapon.second)) {
			ranged->render(target);
		}
	}


	for (auto aoe : this->aoeList) {
		aoe->render(target);
	}

	for (auto mob : this->mobList)
		mob->render(target);

	if (this->player.bomb->active) {
		this->player.bomb->render(target);
	}
	
	this->player.render(target);

	this->ui.render(target);
}