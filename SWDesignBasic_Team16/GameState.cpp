#include "GameState.h"

void GameState::initStages()
{
	// adding stages to deque
	this->stages.push_back(new Stage(1, this->mappedSprite));
	this->stages.push_back(new Stage(2, this->mappedSprite));
	this->stages.push_back(new Stage(3, this->mappedSprite));
	this->stages.push_back(new Stage(4, this->mappedSprite));
	this->stages.push_back(new Stage(5, this->mappedSprite));

	this->nowStage = this->stages.front();
	printf("[Stage %d]\n", this->nowStage->level);

}

GameState::GameState(sf::RenderWindow* window) : State(window) {
	this->font = new sf::Font();
	this->font->loadFromFile("./Resources/Arial.ttf");

	this->allTextures = new sf::Texture();
	this->allTextures->loadFromFile("./Resources/Textures.png");

	this->mappedSprite = new std::map<std::string, sf::Sprite*>();
	this->mappedSprite->emplace("Normal Zombie", new sf::Sprite(*this->allTextures, sf::IntRect(0, 0, 20, 20)));
	this->mappedSprite->emplace("Fast Zombie", new sf::Sprite(*this->allTextures, sf::IntRect(20, 0, 15, 15)));
	this->mappedSprite->emplace("Helmet Zombie", new sf::Sprite(*this->allTextures, sf::IntRect(0, 20, 30, 30)));
	this->mappedSprite->emplace("Shooting Zombie", new sf::Sprite(*this->allTextures, sf::IntRect(40, 0, 20, 20)));
	this->mappedSprite->emplace("Brick Zombie", new sf::Sprite(*this->allTextures, sf::IntRect(30, 20, 30, 30)));

	this->mappedSprite->emplace("Boss I", new sf::Sprite(*this->allTextures, sf::IntRect(80, 0, 50, 50)));
	this->mappedSprite->emplace("Boss II", new sf::Sprite(*this->allTextures, sf::IntRect(80, 0, 50, 50)));
	this->mappedSprite->emplace("Boss III", new sf::Sprite(*this->allTextures, sf::IntRect(80, 0, 50, 50)));
	this->mappedSprite->emplace("Boss IV", new sf::Sprite(*this->allTextures, sf::IntRect(80, 0, 50, 50)));
	this->mappedSprite->emplace("Boss V", new sf::Sprite(*this->allTextures, sf::IntRect(80, 0, 50, 50)));

	this->mappedSprite->emplace("Gold", new sf::Sprite(*this->allTextures, sf::IntRect(524, 0, 16, 16)));
	this->mappedSprite->emplace("Bomb", new sf::Sprite(*this->allTextures, sf::IntRect(524, 16, 16, 16)));
	this->mappedSprite->emplace("Xp", new sf::Sprite(*this->allTextures, sf::IntRect(524, 32, 16, 16)));
	this->mappedSprite->emplace("Magnet", new sf::Sprite(*this->allTextures, sf::IntRect(524, 48, 16, 16)));
	this->mappedSprite->emplace("Potion", new sf::Sprite(*this->allTextures, sf::IntRect(524, 64, 16, 16)));
	this->mappedSprite->emplace("Ice", new sf::Sprite(*this->allTextures, sf::IntRect(524, 80, 16, 16)));

	this->ui = GameUI(sf::Vector2f(640, 360), this->font, this->allTextures);
	
	this->border.setSize(sf::Vector2f(3840, 360));
	this->border.setPosition(sf::Vector2f(-1280, 180));
	this->border.setFillColor(sf::Color::Transparent);
	this->border.setOutlineColor(sf::Color::Red);
	this->border.setOutlineThickness(1.f);

	this->window->setView(view);

	this->initStages();
	// this->initFirstStage();

	this->timeUntilItemCooldown[0] = 1.f;
	this->timeUntilItemCooldown[1] = 1.f;
	this->timeUntilItemCooldown[2] = 1.f;
	this->player.invincible = false;
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
	if (this->player.cx >= 640) {
		for (int i = 0; i < this->nowStage->waveCount; i++) {
			Mob* mob = this->nowStage->spawnMob();
			if (mob == nullptr) return;

			mob->cx = this->player.cx + 640;//this->player.cx + diff.first;
			mob->cy = 360 + Random::instance().getInt(-180, 180); //this->player.cy + diff.second;
			this->mobList.push_back(mob);
			mob->originSpeed = mob->movementSpeed;
			//std::cout << mobList.size() << std::endl;
		}
	}
	else {
		for (int i = 0; i < this->nowStage->waveCount; i++) {
			Mob* mob = this->nowStage->spawnMob();
			if (mob == nullptr) return;

			mob->cx = this->player.cx - 640;//this->player.cx + diff.first;
			mob->cy = 360 + Random::instance().getInt(-180, 180); //this->player.cy + diff.second;
			this->mobList.push_back(mob);
			mob->originSpeed = mob->movementSpeed;
			//std::cout << mobList.size() << std::endl;
		}
	}
}

void GameState::spawnBoss() {
	Mob* boss = this->nowStage->spawnBoss();
	if (this->player.cx >= 640) {
		boss->cx = this->player.cx + 640;//this->player.cx + diff.first;
		boss->cy = 360;//this->player.cy + diff.second;
	}
	else {
		boss->cx = this->player.cx - 640;//this->player.cx + diff.first;
		boss->cy = 360;//this->player.cy + diff.second;
	}
	this->mobList.push_back(boss);
	boss->originSpeed = boss->movementSpeed;
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
					auto direction1 = CustomMath::normalize(sf::Vector2f(this->player.cx, this->player.cy) - sf::Vector2f(this->mobList[i]->cx, this->mobList[i]->cy));
					auto direction2 = CustomMath::normalize(sf::Vector2f(this->player.cx, this->player.cy) - sf::Vector2f(this->mobList[j]->cx, this->mobList[j]->cy));
					auto distance1 = CustomMath::normalize(sf::Vector2f(this->mobList[i]->cx, this->mobList[i]->cy) - sf::Vector2f(this->mobList[j]->cx, this->mobList[j]->cy));
					auto distance2 = CustomMath::normalize(sf::Vector2f(this->mobList[j]->cx, this->mobList[j]->cy) - sf::Vector2f(this->mobList[i]->cx, this->mobList[i]->cy));
					this->mobList[i]->direction = CustomMath::normalize(direction1 + distance1);
					this->mobList[j]->direction = CustomMath::normalize(direction2 + distance2);
				}
			}
		}

		if (mobBounds.intersects(playerNextPosBounds)) {
			player.updateCollision(mobList[i]);
		}
		for (auto partner : this->player.partners) {
			if (mobBounds.intersects(partner->shape.getGlobalBounds())) {
				partner->updateCollision(mobList[i]);
			}
		}
	}


	for (int i = 0; i < this->mobList.size(); i++) {
		sf::FloatRect mobBounds = mobList[i]->getShape().getGlobalBounds();
		if (mobList[i]->weapon != nullptr) {
			if (MeleeWeapon* melee = dynamic_cast<MeleeWeapon*>(mobList[i]->weapon)) {
				sf::FloatRect weaponBounds = melee->shape.getGlobalBounds();
				if (playerNextPosBounds.intersects(weaponBounds) && melee->active) {
					this->player.updateCollision(melee);
				}
				for (auto partner : this->player.partners) {
					if (weaponBounds.intersects(partner->shape.getGlobalBounds())) {
						partner->updateCollision(melee);
					}
				}
			}
			if (RangedWeapon* ranged = dynamic_cast<RangedWeapon*>(mobList[i]->weapon)) {
				for (auto bullet : ranged->bullets) {
					sf::FloatRect bulletBounds = bullet->shape.getGlobalBounds();
					if (playerNextPosBounds.intersects(bulletBounds)) {
						this->player.updateCollision(ranged);
						if (bullet->explosion) {
							this->aoeList.push_back(bullet->explode(ranged->radius, ranged->explosionDuration, ranged->explosionDamage, mobList[i]->shape.getPosition()));
							bullet->explosion = false;
						}
						bullet->out = true;
					}
					for (auto partner : this->player.partners) {
						if (bulletBounds.intersects(partner->shape.getGlobalBounds())) {
							partner->updateCollision(ranged);
							if (bullet->explosion) {
								this->aoeList.push_back(bullet->explode(ranged->radius, ranged->explosionDuration, ranged->explosionDamage, mobList[i]->shape.getPosition()));
								bullet->explosion = false;
							}
							bullet->out = true;
						}
					}
				}
			}
		}

		for (auto item : this->player.itemList) {
			AoeItem* aoeItem = (AoeItem*)item.second;
			sf::FloatRect aoeItemBounds = aoeItem->shape.getGlobalBounds();
			if (mobBounds.intersects(aoeItemBounds) && aoeItem->active) {
				mobList[i]->updateItemCollision(aoeItem, this->player.power);
				this->totalDamage += aoeItem->damage * this->player.power;
			}
		}
		
		for (auto weapon : *this->player.weaponList) {
			if (MeleeWeapon* melee = dynamic_cast<MeleeWeapon*>(weapon.second)) {
				sf::FloatRect weaponBounds = melee->shape.getGlobalBounds();
					if (mobBounds.intersects(weaponBounds) && melee->active) {
						// printf("Collision\n");
						mobList[i]->updateCollision(melee, this->player.power);
						this->totalDamage += melee->damage * this->player.power;
					}
			}
			else if (RangedWeapon* ranged = dynamic_cast<RangedWeapon*>(weapon.second)) {
				for (auto bullet : ranged->bullets) {
					sf::FloatRect bulletBounds = bullet->shape.getGlobalBounds();
					
						if (mobBounds.intersects(bulletBounds)) {
							mobList[i]->updateCollision(ranged, this->player.power);
							this->totalDamage += ranged->damage * this->player.power;

							if (bullet->maxHitCount <= bullet->hitCount) {
								if (bullet->explosion) {
									this->aoeList.push_back(bullet->explode(ranged->radius, ranged->explosionDuration, ranged->explosionDamage, mobList[i]->shape.getPosition()));
									bullet->explosion = false;
								}
								bullet->out = true;
							}
							else bullet->hitCount++;
						}
					
				}
			}
		}
		
		for (auto partner : this->player.partners) {
			if (RangedWeapon* partnerRanged = dynamic_cast<RangedWeapon*>(partner->weapon)) {
				for (auto partnerBullet : partnerRanged->bullets) {
					sf::FloatRect partnerBulletBounds = partnerBullet->shape.getGlobalBounds();

					if (mobBounds.intersects(partnerBulletBounds)) {
						mobList[i]->updateCollision(partnerRanged, this->player.power);
						this->totalDamage += partnerRanged->damage * this->player.power;

						if (partnerBullet->maxHitCount <= partnerBullet->hitCount) {
							if (partnerBullet->explosion) {
								this->aoeList.push_back(partnerBullet->explode(partnerRanged->radius, partnerRanged->explosionDuration, partnerRanged->explosionDamage, mobList[i]->shape.getPosition()));
								partnerBullet->explosion = false;
							}
							partnerBullet->out = true;
						}
						else partnerBullet->hitCount++;
					}

				}
			}
		}
		

		if (mobList[i]->getDeath()) {
			float itemOffset = 12.f;
			DropItem* dropGold = new DropItem(mobList[i]->shape.getPosition() + sf::Vector2f(itemOffset * 1.723f, itemOffset * 1.f), mobList[i]->inventory, this->mappedSprite->at("Gold"));
			dropGoldList.push_back(dropGold);
			DropItem* dropXp = new DropItem(mobList[i]->shape.getPosition() + sf::Vector2f(itemOffset * -1.732f, itemOffset * 1.f), mobList[i]->inventory, this->mappedSprite->at("Xp"));
			dropXpList.push_back(dropXp);

			//auto a = dropGold->getPosition();
			//auto b = dropXp->getPosition();
			//printf("[%.2f, %.2f && %.2f, %.2f]\n", a.x, a.y, b.x, b.y);

			Random* random = NULL;
			if (random->eventOccursWithProbability(0.001f)) {
				DropItem* dropBomb = new DropItem(mobList[i]->shape.getPosition() + sf::Vector2f(0.f, itemOffset * 2.f), mobList[i]->inventory, this->mappedSprite->at("Bomb"));
				dropBomb->shape.setOutlineColor(sf::Color::White);
				dropBomb->shape.setOutlineThickness(1.f);
				dropBombList.push_back(dropBomb);
			}
			if (random->eventOccursWithProbability(0.001f)) {
				DropItem* dropIce = new DropItem(mobList[i]->shape.getPosition() + sf::Vector2f(itemOffset * -1.732f, itemOffset * -1.f), mobList[i]->inventory, this->mappedSprite->at("Ice"));
				dropIceList.push_back(dropIce);
			}
			if (random->eventOccursWithProbability(0.001f)) {
				DropItem* dropPotion = new DropItem(mobList[i]->shape.getPosition() + sf::Vector2f(0.f, itemOffset * -2.f), mobList[i]->inventory, this->mappedSprite->at("Potion"));
				dropPotionList.push_back(dropPotion);
			}
			if (random->eventOccursWithProbability(0.01f)) {
				DropItem* dropMagnetic = new DropItem(mobList[i]->shape.getPosition() + sf::Vector2f(itemOffset * 1.723f, itemOffset * -1.f), mobList[i]->inventory, this->mappedSprite->at("Magnet"));
				dropMagneticList.push_back(dropMagnetic);
			}

			this->xpList.push_back(this->mobList[i]->getXP());
			this->goldList.push_back(this->mobList[i]->getGold());

			delete mobList[i];
			this->mobList.erase(this->mobList.begin() + i);

			this->nowStage->leftKillCountUntilBoss--;
			this->totalKillCount++;
		}
	}

	for (auto aoe : this->aoeList) {
		sf::FloatRect aoeBounds = aoe->shape.getGlobalBounds();
		if (aoe->mobTarget) {
			for (int i = 0; i < this->mobList.size(); i++) {
				sf::FloatRect mobBounds = mobList[i]->getShape().getGlobalBounds();
				if (mobBounds.intersects(aoeBounds)) {
					mobList[i]->updateCollision(aoe, this->player.power);
					this->totalDamage += aoe->damage * this->player.power * .5f;
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
				this->player.inventory.setGold(this->player.inventory.getGold() + this->goldList[i]);
				this->totalGold += this->goldList[i];
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
				this->player.inventory.setXp(this->player.inventory.getXp() + this->xpList[i]);
				this->totalXp += this->xpList[i];
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
			
			player.getBomb();
			std::cout << "Get a Bomb" << std::endl;
			
			//this->aoeList.push_back(new AoE(400.f, 0.3f, 16.f, dropBombList[i]->shape.getPosition()));
			
			delete dropBombList[i];
			this->dropBombList.erase(this->dropBombList.begin() + i);
		}
	}

	for (int i = 0; i < this->dropIceList.size(); i++) {
		sf::FloatRect dropIceBounds = dropIceList[i]->shape.getGlobalBounds();
		if (dropIceBounds.intersects(playerNextPosBounds)) {
			for (int j = 0; j < mobList.size(); j++) {
				if (mobList[j]->movementSpeed == 0 && mobList[j]->freeze == true) mobList[j]->speedZeroDuration = 0.f;
			}
			player.getIce();
			std::cout << "Get a Ice" << std::endl;
			
			//this->aoeList.push_back(new AoE(400.f, 0.3f, dropIceList[i]->shape.getPosition(), 10));
			
			delete dropIceList[i];
			this->dropIceList.erase(this->dropIceList.begin() + i);
		}
	}

	for (int i = 0; i < this->dropPotionList.size(); i++) {
		sf::FloatRect dropPotionBounds = dropPotionList[i]->shape.getGlobalBounds();
		if (dropPotionBounds.intersects(playerNextPosBounds)) {

			player.getPotion();
			std::cout << "Get a Potion" << std::endl;

			delete dropPotionList[i];
			this->dropPotionList.erase(this->dropPotionList.begin() + i);
		}
	}

	for (int i = 0; i < this->dropMagneticList.size(); i++) {
		sf::FloatRect dropMagneticBounds = dropMagneticList[i]->shape.getGlobalBounds();
		if (dropMagneticBounds.intersects(playerNextPosBounds)) {
			for (int j = 0; j < this->dropBombList.size(); j++) {
				player.getBomb();
				//this->aoeList.push_back(new AoE(400.f, 0.3f, 10.f, sf::Vector2f(this->player.cx, this->player.cy)));
				delete dropBombList[j];
			}
			for (int j = 0; j < this->dropIceList.size(); j++) {
				for (int k = 0; k < mobList.size(); k++) {
					mobList[k]->speedZeroDuration = 0.f;
				}
				player.getIce();
				//this->aoeList.push_back(new AoE(400.f, 0.3f, sf::Vector2f(this->player.cx, this->player.cy), 1));
				delete dropIceList[j];
			}
			for (int j = 0; j < this->dropPotionList.size(); j++) {
				player.getPotion();
				delete dropPotionList[j];
			}
			for (int j = 0; j < this->dropXpList.size(); j++) {
				if (xpList[j] != NULL) {
					this->player.inventory.setXp(this->player.inventory.getXp() + this->xpList[j]);
					this->totalXp += this->xpList[j];
				}
				delete dropXpList[j];
			}
			for (int j = 0; j < this->dropGoldList.size(); j++) {
				if (goldList[j] != NULL) {
					this->player.inventory.setGold(this->player.inventory.getGold() + this->goldList[j]);
					this->totalGold += this->goldList[j];
				}
				delete dropGoldList[j];
			}
			this->dropBombList.clear();
			this->dropIceList.clear();
			this->dropPotionList.clear();
			this->dropXpList.clear();
			this->dropGoldList.clear();

			for (auto dropMagnetic : this->dropMagneticList) {
				delete dropMagnetic;
			}
			this->dropMagneticList.clear();
			break;
		}
	}

	for (int i = 0; i < this->player.partners.size(); i++) {
		if (this->player.partners[i]->getDeath()) {
			delete this->player.partners[i];
			this->player.partners.erase(this->player.partners.begin() + i);
			for (int j = i; j < this->player.partners.size(); j++) this->player.partners[j]->index = j + 1;
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

	for (auto i = 1; i <= 3; i++) {
		if (this->timeUntilItemCooldown[i - 1] < 0.01f && sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(sf::Keyboard::Num1 - 1 + i))) {
			// 아이템 사용 쿨다운 조정
			bool res = this->player.useItem(i);
			if (i == 2 && res == true) this->aoeList.push_back(new AoE(200.f, 0.3f, 5.f, sf::Vector2f(this->player.cx, this->player.cy)));
			else if (i == 3 && res == true) this->aoeList.push_back(new AoE(200.f, 0.3f, sf::Vector2f(this->player.cx, this->player.cy), 10));
			this->timeUntilItemCooldown[i - 1] = res ? 1.f : .1f;
		}
	}

}

void GameState::updateItemUse(const float& dt) {
	this->timeUntilItemCooldown[0] -= dt;
	this->timeUntilItemCooldown[1] -= dt;
	this->timeUntilItemCooldown[2] -= dt;

	for (int i = 0; i < this->mobList.size(); i++) {
		if (mobList[i]->movementSpeed == 0 && mobList[i]->freeze == true) {
			if (mobList[i]->isSprite)
				mobList[i]->sprite.setColor(sf::Color(255, 255, 255, 96));
			else
				mobList[i]->shape.setFillColor(sf::Color::Blue);

			mobList[i]->speedZeroDuration += dt;
		}
		if (mobList[i]->speedZeroDuration >= 3.f) {
			if (mobList[i]->isSprite)
				mobList[i]->sprite.setColor(sf::Color::White);
			else
				mobList[i]->shape.setFillColor(sf::Color::Green);

			mobList[i]->freeze = false;
			mobList[i]->speedZeroDuration = 0.f;
			mobList[i]->movementSpeed = mobList[i]->originSpeed;
		}
	}

	for (int i = 0; i < 3; i++) {
		if (this->timeUntilItemCooldown[i] <= 0)
			this->timeUntilItemCooldown[i] = 0.f;
	}
}

void GameState::updateMobSpawn(const float& dt) {
	if (this->mobList.empty()) this->nowStage->nextSpawnTime = 0;
	if (this->nowStage->nextSpawnTime == 0.f && this->mobList.size() < this->nowStage->maxMobCount) {
		this->spawnMob();
	}

	if (!this->nowStage->isBossSpawned && 
		(this->nowStage->bossSpawnTime == 0.f || this->nowStage->leftKillCountUntilBoss <= 0)) {
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
			this->player.getPartner();
			break;
		case 2:
			this->player.getBomb();
			this->player.getPartner();
			break;
		case 3:
			this->player.getIce();
			this->player.getPartner();
			break;
		case 4:
			this->player.inventory.setXp(this->player.level * (this->player.level + 20));
			this->player.getPartner();
			break;
		case 5:
			this->player.getBomb();
			this->player.getIce();
			this->player.inventory.setXp(this->player.level * (this->player.level + 20));
			this->player.getPartner();
			break;
		default:
			break;
		}
	}
	else {
		switch (this->nowStage->level)
		{
		case 1:
			this->player.inventory.setGold(this->player.inventory.getGold() + 10);
			this->player.getPartner();
			break;
		case 2:
			this->aoeList.push_back(new AoE(200, .25f, 1.f, this->npcEventPos, false));
			this->nowStage->enqueueMob(1, 2, "Normal Zombie", 3, 1, 400, sf::Color::Green, 20/*size*/, 1, false, 0);
			this->mobList.at(this->mobList.size() - 1)->cx = this->npcEventPos.x;
			this->mobList.at(this->mobList.size() - 1)->cy = this->npcEventPos.y;
			this->mobList.at(this->mobList.size() - 1)->shape.setPosition(this->npcEventPos);
			break;
		case 3:
			this->aoeList.push_back(new AoE(200, .25f, 1.f, this->npcEventPos, false));
			this->nowStage->enqueueMob(1, 2, "Normal Zombie", 3, 1, 400, sf::Color::Green, 20/*size*/, 1, false, 0);
			this->mobList.at(this->mobList.size() - 1)->cx = this->npcEventPos.x;
			this->mobList.at(this->mobList.size() - 1)->cy = this->npcEventPos.y;
			this->mobList.at(this->mobList.size() - 1)->shape.setPosition(this->npcEventPos);
			break;
		case 4:
			this->aoeList.push_back(new AoE(200, .25f, 1.f, this->npcEventPos, false));
			this->nowStage->enqueueMob(1, 2, "Normal Zombie", 3, 1, 400, sf::Color::Green, 20/*size*/, 1, false, 0);
			this->mobList.at(this->mobList.size() - 1)->cx = this->npcEventPos.x;
			this->mobList.at(this->mobList.size() - 1)->cy = this->npcEventPos.y;
			this->mobList.at(this->mobList.size() - 1)->shape.setPosition(this->npcEventPos);
			break;
		case 5:
			this->aoeList.push_back(new AoE(200, .25f, 1.f, this->npcEventPos, false));
			this->nowStage->enqueueMob(1, 2, "Normal Zombie", 3, 1, 400, sf::Color::Green, 20/*size*/, 1, false, 0);
			this->mobList.at(this->mobList.size() - 1)->cx = this->npcEventPos.x;
			this->mobList.at(this->mobList.size() - 1)->cy = this->npcEventPos.y;
			this->mobList.at(this->mobList.size() - 1)->shape.setPosition(this->npcEventPos);
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
		this->player.hp = this->player.maxHp;
		for (int j = 0; j < this->dropBombList.size(); j++) {
			player.getBomb();
			delete dropBombList[j];
		}
		for (int j = 0; j < this->dropIceList.size(); j++) {
			for (int k = 0; k < mobList.size(); k++) {
				mobList[k]->speedZeroDuration = 0.f;
			}
			player.getIce();
			delete dropIceList[j];
		}
		for (int j = 0; j < this->dropPotionList.size(); j++) {
			player.getPotion();
			delete dropPotionList[j];
		}
		for (int j = 0; j < this->dropXpList.size(); j++) {
			if (xpList[j] != NULL) {
				this->player.inventory.setXp(this->player.inventory.getXp() + this->xpList[j]);
			}
			delete dropXpList[j];
		}
		for (int j = 0; j < this->dropGoldList.size(); j++) {
			if (goldList[j] != NULL) {
				this->player.inventory.setGold(this->player.inventory.getGold() + this->goldList[j]);
			}
			delete dropGoldList[j];
		}
		for (int j = 0; j < this->dropMagneticList.size(); j++) {
			delete dropMagneticList[j];
		}
		this->dropBombList.clear();
		this->dropIceList.clear();
		this->dropPotionList.clear();
		this->dropXpList.clear();
		this->dropGoldList.clear();
		this->dropMagneticList.clear();

		this->stages.pop_front();

		if (this->stages.empty()) {
			this->allClear = true; // TODO: 올 클리어 추가해야함
			this->quit = true;
			return;
		}
		this->eventQueue.push_back(new StoreEvent(&this->player));
		for (auto npc : this->npcList) {
			delete npc;
		}
		this->npcList.clear();
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
	if (this->player.inventory.getXp() >= CustomMath::getMaxXp(this->player.level)) {
		this->player.inventory.setXp(this->player.inventory.getXp() - CustomMath::getMaxXp(this->player.level));
		this->player.level++;
		this->eventQueue.push_back(new OptionSelectionEvent(&this->player));
	}

	this->view.setCenter(this->player.cx, this->player.cy);
	this->window->setView(view);

	for (auto partner : this->player.partners) {
		partner->update(dt, this->player.cx, this->player.cy, this->player.viewDirection);
		partner->weapon->update(dt, partner->shape, partner->cx, partner->cy, partner->viewDirection);
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
	this->ui.updateItemSlot(this->timeUntilItemCooldown, this->player.remainPotion, this->player.remainBomb, this->player.remainIce);
	this->ui.updateLevelText(this->player.level);
	this->ui.updateGoldText(this->player.inventory.getGold());
	this->ui.updateStageText(this->nowStage->level);
	this->ui.updatePlayTimeText(this->playTime);

	this->updateStageClear();
}

void GameState::render(sf::RenderTarget* target) {
	// 맵 출력이 플레이어보다 앞서야 함
	this->backgroundMap.render(target);
	target->draw(border);

	for (auto npc : this->npcList)
		npc->render(target);

	for (auto dropGold : this->dropGoldList)
		dropGold->draw(target);

	for (auto dropXp : this->dropXpList)
		dropXp->draw(target);

	for (auto dropBomb : this->dropBombList)
		dropBomb->draw(target);

	for (auto dropIce : this->dropIceList)
		dropIce->draw(target);

	for (auto dropPotion : this->dropPotionList)
		dropPotion->draw(target);

	for (auto dropMagnetic : this->dropMagneticList)
		dropMagnetic->draw(target);

	for (auto weapon : *this->player.weaponList) {
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
	
	for (auto partner : this->player.partners) {
		partner->render(target);
		partner->weapon->render(target);
	}
	

	this->ui.render(target);
}