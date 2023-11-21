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

void GameState::initPlayerHpBar()
{
	
}

GameState::GameState(sf::RenderWindow* window) : State(window) {
	this->xp = 0;
	this->level = 0;
	this->ui = GameUI(sf::Vector2f(640, 360));

	this->view.setCenter(sf::Vector2f(640.f, 360.f));
	this->view.setSize(sf::Vector2f(1280.f, 720.f));
	this->window->setView(view);

	this->initStages();
	this->initPlayerHpBar();

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
	sf::FloatRect swordBounds = this->player.sword->shape.getGlobalBounds();
	for (int i = 0; i < this->mobList.size(); i++) {
		sf::FloatRect mobBounds = mobList[i]->getShape().getGlobalBounds();
		if (mobBounds.intersects(playerNextPosBounds)) {
			this->player.updateCollision(mobList[i], velocity);
		}
		if (mobBounds.intersects(swordBounds) && this->player.sword->active) {
			// printf("Collision\n");
			mobList[i]->updateCollision(this->player.sword);
			if (mobList[i]->getDeath()) {
				// 
				DropItem* dropitem = new DropItem(mobList[i]->shape.getPosition(), mobList[i]->inventory);
				dropItemList.push_back(dropitem);
				delete mobList[i];
				this->mobList.erase(this->mobList.begin() + i);
			}
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

void GameState::update(const float& dt, int& keyTime) {
	if (keyTime < 4)
		keyTime++;

	this->updateInput(dt, keyTime);
	this->updateCollision(this->velocity);
	this->player.update(dt, this->velocity);

	if (CustomMath::getLength(this->velocity) != 0.f) {
		this->view.move(this->player.movementSpeed * dt * 20 * this->velocity);
		this->window->setView(view);
	}

	this->ui.updateCenterPos(sf::Vector2f(this->player.cx, this->player.cy));
	this->ui.updateHpBar(this->player.hp, 100.f);

	this->updateItemUse(dt);

	this->nowStage->update(dt);
	this->updateMobSpawn(dt);

	for (auto mob : this->mobList) {
		mob->update(dt, sf::Vector2f(this->player.cx, this->player.cy));
	}

	if (this->player.getDeath()) {
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
	
	for (auto dropitem : this->dropItemList)
		dropitem->draw(target);
	
	if (this->player.sword->active) {
		this->player.sword->render(target);
	}

	this->ui.render(target);
}
