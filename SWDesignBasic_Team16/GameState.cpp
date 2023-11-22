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
		Mob* mob = new Mob(2, 2);
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
void GameState::initPlayerXpBar()
{
	xpBar[0] = sf::Vertex(sf::Vector2f(100.f, 110.f), sf::Color::Blue);
	xpBar[1] = sf::Vertex(sf::Vector2f(100.f, 140.f), sf::Color::Blue);
	xpBar[2] = sf::Vertex(sf::Vector2f(1180.f, 140.f), sf::Color::Blue);
	xpBar[3] = sf::Vertex(sf::Vector2f(1180.f, 110.f), sf::Color::Blue);
}

GameState::GameState(sf::RenderWindow* window) : State(window) {
	this->xp = 0;
	this->level = 0;

	this->initStages();
	// this->initFirstStage();
	this->initPlayerHpBar();
	this->initPlayerXpBar();

	this->timeUntilItemCooldown = 1.f;
	this->bombduration = 0.f;
}

GameState::~GameState() {
	for (int i = 0; i < this->mobList.size(); i++) {
		delete this->mobList.at(i);
	}
	this->mobList.clear();
}

void GameState::spawnMob()
{
	Mob* mob = new Mob(2, 2);
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
	Mob* boss = new Mob(100, 20, "Boss", 1.f, 3.f, 300.f);

	this->currentStage.isBossSpawned = true;
	this->mobList.push_back(boss);
}

void GameState::endState() {
	std::cout << "Ending State\n";
}

void GameState::updateCollision(sf::Vector2f& velocity)
{
	sf::FloatRect playerNextPosBounds = this->player.shape.getGlobalBounds();
	sf::FloatRect swordBounds = this->player.sword->shape.getGlobalBounds();
	sf::FloatRect bombBounds = this->player.bomb->shape.getGlobalBounds();
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
				xpList[i] = this->mobList[i]->getXP();
				goldList[i] = this->mobList[i]->getGold();
				delete mobList[i];
				this->mobList.erase(this->mobList.begin() + i);
			}
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

	for (int i = 0; i < this->dropItemList.size(); i++) {
		sf::FloatRect dropItemBounds = dropItemList[i]->shape.getGlobalBounds();
		if (dropItemBounds.intersects(playerNextPosBounds)) {
			//xp += mobList[i]->getXP();
			xp += xpList[i];
			//gold += mobList[i]->getGold();
			gold += goldList[i];
			if (xp % 10 == 0) {
				xp = 0;
				level += 1;
			}

			std::cout << "Level: " << level << ", Xp: " << xp << std::endl;
			std::cout << "Gold:  " << gold << std::endl;

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
	hpBar[0] = sf::Vertex(sf::Vector2f(this->player.cx - 450.f, -305.f + this->player.cy), sf::Color::Red);
	hpBar[1] = sf::Vertex(sf::Vector2f(this->player.cx - 450.f, -350.f + this->player.cy), sf::Color::Red);
	hpBar[2] = sf::Vertex(sf::Vector2f(this->player.cx - 450.f + this->player.hp * 10, -350.f + this->player.cy), sf::Color::Red);
	hpBar[3] = sf::Vertex(sf::Vector2f(this->player.cx - 450.f + this->player.hp * 10, -305.f + this->player.cy), sf::Color::Red);
}

void GameState::updateXpBar()
{
	xpBar[0] = sf::Vertex(sf::Vector2f(this->player.cx - 450.f, -270.f + this->player.cy), sf::Color::Blue);
	xpBar[1] = sf::Vertex(sf::Vector2f(this->player.cx - 450.f, -300.f + this->player.cy), sf::Color::Blue);
	xpBar[2] = sf::Vertex(sf::Vector2f(this->player.cx - 440.f + this->xp * 30, -300.f + this->player.cy), sf::Color::Blue);
	xpBar[3] = sf::Vertex(sf::Vector2f(this->player.cx - 440.f + this->xp * 30, -270.f + this->player.cy), sf::Color::Blue);
}


void GameState::updateStageClear()
{
	if (this->currentStage.isBossSpawned && this->mobList.empty()) {
		std::cout << "Stage 1 Clear" << std::endl;
		this->quit = true;
	}
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
		mob->update(dt, sf::Vector2f(this->player.cx, this->player.cy));
	}

	this->updateHpBar();
	this->updateXpBar();

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

	if (this->player.bomb->active) {
		this->player.bomb->render(target);
	}

	target->draw(hpBar, 4, sf::Quads);
	target->draw(xpBar, 4, sf::Quads);

	sf::Font font;
	font.loadFromFile("C:/Users/USER/source/repos/Zombie-Slayer/fonts/Arial.ttf");
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
	goldText.setString("Gold: " + std::to_string(gold));
	levelText.setString("Level: " + std::to_string(level));

	target->draw(goldText);
	target->draw(levelText);
}