#include "Player.h"

void Player::initVariables()
{
	this->cx = 1280.f / 2;
	this->cy = 720.f / 2;

	this->viewDirection.x = 0.f;
	this->viewDirection.y = 0.f;

	this->selected.push_back(0);
	for (int i = 1; i <= 5; i++)
		this->unselected.push_back(i);
}

void Player::initShape()
{
	this->shape.setSize(sf::Vector2f(this->gridSize, this->gridSize));
	this->shape.setFillColor(sf::Color::White);

	this->shape.setOrigin(sf::Vector2f(this->shape.getLocalBounds().width, this->shape.getLocalBounds().height) / 2.f);
	this->shape.setPosition(this->shape.getPosition().x + this->shape.getOrigin().x, this->shape.getPosition().y + this->shape.getOrigin().y);

	this->shape.setRotation(45);
}

Player::Player() : Entity(200, 10, 100)
{
	this->initShape();
	this->initVariables();

	/*
	* 0: Sword
	* 1: Spear
	* 2: Grinder
	* 3: Pistol
	* 4: Brick
	* 5: Rocket
	*/
	weaponList.insert(std::unordered_map<int, Weapon*>::value_type(0, new Sword(1, 1, .5f, sf::Vector2f(this->cx, this->cy), sf::Color::Red)));
	// weaponList.insert(std::unordered_map<std::string, Weapon*>::value_type("Spear", new Spear(2, 2.5f, .25f, sf::Vector2f(this->cx, this->cy))));
	// weaponList.insert(std::unordered_map<std::string, Weapon*>::value_type("Grinder", new Grinder(0, 1, 0, sf::Vector2f(this->cx, this->cy))));
	// weaponList.insert(std::unordered_map<std::string, Weapon*>::value_type("Pistol", new Pistol(1.f, 20, 2.f, sf::Vector2f(this->cx, this->cy), 10)));
	// weaponList.insert(std::unordered_map<std::string, Weapon*>::value_type("Brick", new Brick(5.f, .5f, 5.f, sf::Vector2f(this->cx, this->cy), 2)));
	// weaponList.insert(std::unordered_map<std::string, Weapon*>::value_type("Rocket", new Rocket(3.f, 0.f, 3.f, sf::Vector2f(this->cx, this->cy), 15, 40.f, 3.f, .1f)));
	remainPotion = 0;
	remainBomb = 0;
	remainIce = 0;
}

Player::~Player()
{
	for (auto weapon : this->weaponList) {
		delete weapon.second;
	}
	this->weaponList.clear();
	
	for (auto item : this->itemList) {
		delete item.second;
	}
	this->itemList.clear();
	
	for (auto partner : this->partners) {
		delete partner;
	}
	this->partners.clear();
}

void Player::attack(const float& dt)
{
	for (auto weapon : this->weaponList) {
		weapon.second->update(dt, this->shape, this->cx, this->cy, this->viewDirection);
	}
	for (auto item : this->itemList) {
		item.second->update(dt, this->shape, this->cx, this->cy);
	}
}

// deprecated
void Player::updateLevel(const float& dt) {}

void Player::updateCollision(Entity* object)
{
	if (Mob* mob = dynamic_cast<Mob*>(object)) {
		if (!this->invincible) this->hp -= mob->power;
	}
}

void Player::updateCollision(Weapon* weapon)
{
	if (!this->invincible) this->hp -= weapon->damage;
}

void Player::updateCollision(AoE* aoe)
{
	if (!this->invincible) this->hp -= aoe->damage;
}

void Player::move(const float& dt, const float dx, const float dy) {
	auto v = CustomMath::normalize(sf::Vector2f(dx, dy));
	this->cx += v.x * this->movementSpeed * dt;
	this->cy += v.y * this->movementSpeed * dt;
}

void Player::render(sf::RenderTarget* target) {
	Entity::render(target);
}

void Player::update(const float& dt, sf::Vector2f velocity) {
	this->move(dt, velocity.x, velocity.y);
	this->attack(dt);
	Entity::update(dt);
}

void Player::getPotion() {
	remainPotion++;
}

void Player::getBomb() {
	remainBomb++;
}

void Player::getIce() {
	remainIce++;
}

bool Player::useItem(int i) {
	if (i == 1) {
		if (remainPotion >= 1) {
			if (this->hp + 20 <= this->maxHp) {
				this->hp += 20;
				remainPotion--;
				std::cout << "Hp UP" << std::endl;
				return true;
			}
			else if (this->hp + 20 > this->maxHp && this->hp < this->maxHp) {
				this->hp = this->maxHp;
				remainPotion--;
				std::cout << "Hp UP" << std::endl;
				return true;
			}
			else if (this->hp == this->maxHp) {
				std::cout << "Your HP is already FULL" << std::endl;
				return false;
			}
		}
		else {
			std::cout << "There's No Item!!!" << std::endl;
			return false;
		}
	}

	if (i == 2) {
		if (remainBomb >= 1) {
			
			remainBomb--;
			std::cout << "Bomb" << std::endl;
			return true;		
		}
		else {
			std::cout << "There's No Item!!!" << std::endl;
			return false;
		}
	}

	if (i == 3) {
		if (remainIce >= 1) {

			remainIce--;
			std::cout << "Freeze" << std::endl;
			return true;
		}
		else {
			std::cout << "There's No Item!!!" << std::endl;
			return false;
		}
	}
	return false;
}

std::string Player::indexToWeaponName(int index)
{
	switch (index)
	{
	case 0:
		return "Sword";
	case 1:
		return "Spear";
	case 2:
		return "Grinder";
	case 3:
		return "Pistol";
	case 4:
		return "Brick";
	case 5:
		return "Rocket";
	}
}

int Player::weaponNameToIndex(std::string name)
{
	if (name == "Sword") return 0;
	if (name == "Spear") return 1;
	if (name == "Grinder") return 2;
	if (name == "Pistol") return 3;
	if (name == "Brick") return 4;
	if (name == "Rocket") return 5;
}

void Player::getPartner()
{
	this->partners.push_back(new Partner(this->cx, this->cy, this->viewDirection, this->partners.size() + 1));
}
