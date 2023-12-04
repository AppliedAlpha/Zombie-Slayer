#include "GameState.h"

void GameState::initStages()
{
	// adding stages to deque
	this->stages.push_back(new Stage(1));
	this->stages.push_back(new Stage(2));
	this->stages.push_back(new Stage(3));
	this->stages.push_back(new Stage(4));

	this->nowStage = this->stages.front();
	printf("[Stage %d]\n", this->nowStage->level);

	// printf("%s\n", this->nowStage->mobList.front()->name.c_str());
}

GameState::GameState(sf::RenderWindow* window) : State(window) {
	this->font = new sf::Font();
	this->font->loadFromFile("./Resources/Arial.ttf");

	this->allTextures = new sf::Texture();
	this->allTextures->loadFromFile("./Resources/Textures.png");

	this->mappedSprite = new std::map<std::string, sf::Sprite*>();
	this->mappedSprite->emplace("Normal Zombie", new sf::Sprite(*this->allTextures, sf::IntRect(0, 0, 20, 20)));

	this->ui = GameUI(sf::Vector2f(640, 360), this->font, this->allTextures);

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
	std::map<std::string, sf::Sprite*>().swap(*this->mappedSprite);

	delete this->allTextures;
	delete this->font;
}

void GameState::spawnMob()
{
	Mob* mob = this->nowStage->spawnMob();

	// 몹의 위치를 스폰되고 나서 GameState에서 정해주는 것으로 변경
	// 반지름 크기는 나중에 변경해줘도 좋을듯
	auto diff = CustomMath::getRandomCoordWithRadius(480.f);

	mob->cx = this->player.cx + diff.first;
	mob->cy = this->player.cy + diff.second;
	this->mobList.push_back(mob);
	//std::cout << mobList.size() << std::endl;
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
	
	for (int i = 0; i < this->mobList.size(); i++) {
		sf::FloatRect mobBounds = mobList[i]->getShape().getGlobalBounds();
		this->mobList[i]->direction = CustomMath::normalize(sf::Vector2f(this->player.cx, this->player.cy) - sf::Vector2f(this->mobList[i]->cx, this->mobList[i]->cy));

		for (int j = 0; j < this->mobList.size(); j++) {
			if (i != j) {
				sf::FloatRect otherMobBounds = mobList[j]->getShape().getGlobalBounds();
				if (mobBounds.intersects(otherMobBounds)) {
					//this->mobList[i]->movementSpeed *= 2;
					float d1 = (this->player.cx - this->mobList[i]->cx) * (this->player.cx - this->mobList[i]->cx) + (this->player.cy - this->mobList[i]->cy) * (this->player.cy - this->mobList[i]->cy);
					float d2 = (this->player.cx - this->mobList[j]->cx) * (this->player.cx - this->mobList[j]->cx) + (this->player.cy - this->mobList[j]->cy) * (this->player.cy - this->mobList[j]->cy);
					if (d1 >= d2) {
						this->mobList[i]->direction = CustomMath::normalize(- this->mobList[i]->direction + this->mobList[j]->direction);
						//this->mobList[i]->direction = sf::Vector2f(0, 0);
						//std::cout << this->mobList[i]->direction.x << ", " << this->mobList[i]->direction.y << std::endl;
					}
					else {
						this->mobList[j]->direction = CustomMath::normalize(- this->mobList[j]->direction + this->mobList[i]->direction);
						//this->mobList[i]->direction = sf::Vector2f(0, 0);
						//std::cout << this->mobList[j]->direction.x << ", " << this->mobList[j]->direction.y << std::endl;
					}
				}
			}
		}

		if (mobBounds.intersects(playerNextPosBounds)) {
			player.updateCollision(mobList[i]);
		}
	}


	for (int i = 0; i < this->mobList.size(); i++) {
		sf::FloatRect mobBounds = mobList[i]->getShape().getGlobalBounds();
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

		for (auto item : this->player.itemList) {
			AoeItem* aoeItem = (AoeItem*)item.second;
			sf::FloatRect aoeItemBounds = aoeItem->shape.getGlobalBounds();
			if (mobBounds.intersects(aoeItemBounds) && aoeItem->active) {
				mobList[i]->updateItemCollision(aoeItem, this->player.power);
			}
		}
		for (auto weapon : this->player.weaponList) {
			if (MeleeWeapon* melee = dynamic_cast<MeleeWeapon*>(weapon.second)) {
				sf::FloatRect weaponBounds = melee->shape.getGlobalBounds();
					if (mobBounds.intersects(weaponBounds) && melee->active) {
						// printf("Collision\n");
						mobList[i]->updateCollision(melee, this->player.power);
					}
				
			}
			else if (RangedWeapon* ranged = dynamic_cast<RangedWeapon*>(weapon.second)) {
				for (auto bullet : ranged->bullets) {
					sf::FloatRect bulletBounds = bullet->shape.getGlobalBounds();
					
						if (mobBounds.intersects(bulletBounds)) {
							mobList[i]->updateCollision(ranged, this->player.power);
							if (bullet->maxHitCount <= bullet->hitCount) {
								if (bullet->explosion) {
									this->aoeList.push_back(bullet->explode(ranged->radius, ranged->explosionDuration, ranged->explosionDamage, mobList[i]->shape.getPosition()));
								}
								bullet->out = true;
							}
							else bullet->hitCount++;
						}
					
				}
			}
		}

		if (mobList[i]->getDeath()) {
			// 
			//DropItem* dropitem = new DropItem(mobList[i]->shape.getPosition(), mobList[i]->inventory);
			DropItem* dropGold = new DropItem(mobList[i]->shape.getPosition() + sf::Vector2f(10.f, 10.f), mobList[i]->inventory, sf::Color(255, 255, 0));
			dropGoldList.push_back(dropGold);
			DropItem* dropXp = new DropItem(mobList[i]->shape.getPosition() + sf::Vector2f(-10.f, 10.f), mobList[i]->inventory, sf::Color(0, 0, 255));
			dropXpList.push_back(dropXp);

			Random* random = NULL;
			if (random->eventOccursWithProbability(0.5f)) {
				DropItem* dropBomb = new DropItem(mobList[i]->shape.getPosition() + sf::Vector2f(10.f, -10.f), mobList[i]->inventory, sf::Color(0, 0, 0));
				dropBombList.push_back(dropBomb);
			}
			if (random->eventOccursWithProbability(0.5f)) {
				DropItem* dropPotion = new DropItem(mobList[i]->shape.getPosition() + sf::Vector2f(-10.f, -10.f), mobList[i]->inventory, sf::Color(255, 0, 0));
				dropPotionList.push_back(dropPotion);
			}

			this->xpList.push_back(this->mobList[i]->getXP());
			this->goldList.push_back(this->mobList[i]->getGold());

			delete mobList[i];
			this->mobList.erase(this->mobList.begin() + i);
		}
	}

	for (auto aoe : this->aoeList) {
		sf::FloatRect aoeBounds = aoe->shape.getGlobalBounds();
		if (aoe->mobTarget) {
			for (int i = 0; i < this->mobList.size(); i++) {
				sf::FloatRect mobBounds = mobList[i]->getShape().getGlobalBounds();
				if (mobBounds.intersects(aoeBounds)) {
					mobList[i]->updateCollision(aoe);
				}
			}
		}
		else {
			if (playerNextPosBounds.intersects(aoeBounds)) {
				this->player.updateCollision(aoe);
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
	for (int i = 0; i < this->dropGoldList.size(); i++) {
		sf::FloatRect dropGoldBounds = dropGoldList[i]->shape.getGlobalBounds();
		if (dropGoldBounds.intersects(playerNextPosBounds)) {
			if (goldList[i] != NULL) {
				//this->player.inventory.setGold(this->player.inventory.getGold() + goldList[i]);
				this->player.inventory.setGold(this->player.inventory.getGold() + this->goldList[i]);
			}
			std::cout << "Gold:  " << this->player.inventory.getGold() << std::endl;

			delete dropGoldList[i];
			this->goldList.erase(this->goldList.begin() + i);
			this->dropGoldList.erase(this->dropGoldList.begin() + i);
		}
	}

	for (int i = 0; i < this->dropXpList.size(); i++) {
		sf::FloatRect dropXpBounds = dropXpList[i]->shape.getGlobalBounds();
		if (dropXpBounds.intersects(playerNextPosBounds)) {
			if (xpList[i] != NULL) {
				//this->player.inventory.setXp(this->player.inventory.getXp() + xpList[i]);
				this->player.inventory.setXp(this->player.inventory.getXp() + this->xpList[i]);
				while (this->player.inventory.getXp() >= CustomMath::getMaxXp(this->player.level)) {
					this->player.inventory.setXp(this->player.inventory.getXp() - CustomMath::getMaxXp(this->player.level));
					this->player.level++;
					this->eventQueue.push_back(new OptionSelectionEvent(&this->player));
				}
			}

			std::cout << "Level: " << this->player.level << ", Xp: " << this->player.inventory.getXp() << std::endl;

			delete dropXpList[i];
			this->xpList.erase(this->xpList.begin() + i);
			this->dropXpList.erase(this->dropXpList.begin() + i);
		}
	}

	for (int i = 0; i < this->dropBombList.size(); i++) {
		sf::FloatRect dropBombBounds = dropBombList[i]->shape.getGlobalBounds();
		if (dropBombBounds.intersects(playerNextPosBounds)) {
			this->aoeList.push_back(new AoE(400.f, 0.3f, 6.f, dropBombList[i]->shape.getPosition()));
			/*
			for (auto item : this->player.itemList) {
				item.second->active = true;
			}
			std::cout << "Bomb!!!" << std::endl;
			*/
			delete dropBombList[i];
			this->dropBombList.erase(this->dropBombList.begin() + i);
		}
	}

	for (int i = 0; i < this->dropPotionList.size(); i++) {
		sf::FloatRect dropPotionBounds = dropPotionList[i]->shape.getGlobalBounds();
		if (dropPotionBounds.intersects(playerNextPosBounds)) {

			player.getPotion();
			std::cout << "Get a Potion!!!" << std::endl;

			delete dropPotionList[i];
			this->dropPotionList.erase(this->dropPotionList.begin() + i);
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
			this->player.useItem(i);

			this->timeUntilItemCooldown = 1.f;
		}
	}

}

void GameState::updateItemUse(const float& dt) {
	this->timeUntilItemCooldown -= dt;
	for (auto item : this->player.itemList) {
		if (item.second->active == true) this->bombduration += dt;
		if (this->bombduration >= 0.3f) {
			item.second->active = false;
			bombduration = 0.f;
		}
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
			break;
		case 2:
			this->aoeList.push_back(new AoE(200, .5f, 1.f, this->npcEventPos));
			break;
		case 3:
			this->player.movementSpeed = this->player.movementSpeed + 10;
			break;
		case 4:
			this->mobList.push_back(new Mob(2, 2, std::string("Normal Zombie"), 3.f, 1.f, 40.f/*80*/, sf::Color::Green, 20.f));
			this->mobList.at(this->mobList.size() - 1)->cx = this->npcEventPos.x;
			this->mobList.at(this->mobList.size() - 1)->cy = this->npcEventPos.y;
			this->mobList.at(this->mobList.size() - 1)->shape.setPosition(this->npcEventPos);
			break;
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
			break;
		case 2:
			this->aoeList.push_back(new AoE(200, .5f, 1.f, this->npcEventPos, false));
			break;
		case 3:
			this->player.movementSpeed = this->player.movementSpeed - 10;
			break;
		case 4:
			this->mobList.push_back(new Mob(2, 2, std::string("Normal Zombie"), 3.f, 1.f, 40.f/*80*/, sf::Color::Green, 20.f));
			this->mobList.at(this->mobList.size() - 1)->cx = this->npcEventPos.x;
			this->mobList.at(this->mobList.size() - 1)->cy = this->npcEventPos.y;
			this->mobList.at(this->mobList.size() - 1)->shape.setPosition(this->npcEventPos);
			break;
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
			this->allClear = true;
			return;
		}

		this->nowStage = this->stages.front();
		this->backgroundMap.changeSpriteByStage(this->nowStage->level);
	}
}

void GameState::update(const float& dt) {
	if (inputTerm < 10) {
		inputTerm++;
	}

	this->updateInput(dt);
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

	if (this->npcEvent != -1) {
		this->updateNPCEvent(dt);
	}

	for (auto npc : this->npcList) {
		npc->update(dt);
	}

	if (this->player.hp <= 0) {
		this->quit = true;
	}
	this->updateCollision(this->velocity);
	for (auto mob : this->mobList) {
		mob->update(dt, sf::Vector2f(mob->direction.x, mob->direction.y));
	}
	this->playTime += dt;

	// ui update
	this->ui.updateCenterPos(sf::Vector2f(this->player.cx, this->player.cy));
	this->ui.updateHpBar(this->player.hp, this->player.maxHp);
	this->ui.updateXpBar(this->player.inventory.getXp(), CustomMath::getMaxXp(this->player.level));
	this->ui.updateItemSlot(this->timeUntilItemCooldown, this->player.remainPotion);
	this->ui.updateLevelText(this->player.level);
	this->ui.updateGoldText(this->player.inventory.getGold());
	this->ui.updateStageText(this->nowStage->level);
	this->ui.updatePlayTimeText(this->playTime);

	this->updateStageClear();
}

void GameState::render(sf::RenderTarget* target) {
	// 맵 출력이 플레이어보다 앞서야 함
	this->backgroundMap.render(target);

	for (auto npc : this->npcList)
		npc->render(target);

	for (auto dropGold : this->dropGoldList)
		dropGold->draw(target);

	for (auto dropXp : this->dropXpList)
		dropXp->draw(target);

	for (auto dropBomb : this->dropBombList)
		dropBomb->draw(target);

	for (auto dropPotion : this->dropPotionList)
		dropPotion->draw(target);

	for (auto weapon : this->player.weaponList) {
		if (MeleeWeapon* melee = dynamic_cast<MeleeWeapon*>(weapon.second)) {
			if (melee->active)
				melee->render(target);
		}
		else if (RangedWeapon* ranged = dynamic_cast<RangedWeapon*>(weapon.second)) {
			ranged->render(target);
		}
	}


	for (auto mob : this->mobList) {
		mob->render(target);
	}

	for (auto aoe : this->aoeList) {
		aoe->render(target);
	}
	
	for (auto item : this->player.itemList) {
		if (item.second->active) {
			item.second->render(target);
		}
	}
	
	this->player.render(target);

	this->ui.render(target);
}