#include "Player.h"

void Player::initVariables()
{
	this->cx = 1280.f / 2;
	this->cy = 720.f / 2;

	this->viewDirection.x = 0.f;
	this->viewDirection.y = 0.f;
}

void Player::initShape()
{
	this->shape.setSize(sf::Vector2f(this->gridSize, this->gridSize));
	this->shape.setFillColor(sf::Color::White);

	this->shape.setOrigin(sf::Vector2f(this->shape.getLocalBounds().width, this->shape.getLocalBounds().height) / 2.f);
	this->shape.setPosition(this->shape.getPosition().x + this->shape.getOrigin().x, this->shape.getPosition().y + this->shape.getOrigin().y);

	this->shape.setRotation(45);
}

Player::Player() : Entity(200, 1, 100)
{
	this->initShape();
	this->initVariables();

	// TODO: 맨 처음에 무기 구석에 있는 거 고치기
	weaponList.insert(std::unordered_map<std::string, Weapon*>::value_type("Sword", new Sword(1, 1, .5f, sf::Vector2f(this->cx, this->cy))));
	weaponList.insert(std::unordered_map<std::string, Weapon*>::value_type("Spear", new Spear(2, 2.5f, .25f, sf::Vector2f(this->cx, this->cy))));
	weaponList.insert(std::unordered_map<std::string, Weapon*>::value_type("Grinder", new Grinder(0, 1, 0, sf::Vector2f(this->cx, this->cy))));
	weaponList.insert(std::unordered_map<std::string, Weapon*>::value_type("Pistol", new Pistol(1.f, 20, 2.f, sf::Vector2f(this->cx, this->cy), 10)));
	weaponList.insert(std::unordered_map<std::string, Weapon*>::value_type("Brick", new Brick(5.f, .5f, 5.f, sf::Vector2f(this->cx, this->cy), 2)));
	weaponList.insert(std::unordered_map<std::string, Weapon*>::value_type("Rocket", new Rocket(3.f, 0.f, 3.f, sf::Vector2f(this->cx, this->cy), 15, 40.f, 3.f, .1f)));
	// weaponList.insert(std::unordered_map<std::string, Weapon*>::value_type("Grinder", new Grinder(0, 1, 0)));
	// weaponList.push_back(new Sword(1, 1, .5f));
	// weaponList.push_back(new Spear(2, 2.5f, .5f));
	// weaponList.push_back(new Grinder(0, .5f, .1f));
	this->bomb = new Bomb(1, 10, .5f);
}

Player::~Player()
{
	for (auto weapon : this->weaponList) {
		delete weapon.second;
	}
	this->weaponList.clear();
	delete this->bomb;
}

void Player::attack(const float& dt)
{
	for (auto weapon : this->weaponList) {
		weapon.second->update(dt, this->shape, this->cx, this->cy, this->viewDirection);
	}
}

void Player::updateLevel(const float& dt)
{
	if (this->inventory.getXp() >= 10) {
		this->level = this->level + this->inventory.getXp() / 10;
		this->inventory.setXp(this->inventory.getXp() - 10);
	}
	std::cout << "Level: " << this->level << ", Xp: " << this->inventory.getXp() << std::endl;

}

void Player::updateCollision(Entity* object)
{
	if (Mob* mob = dynamic_cast<Mob*>(object)) {
		if (!this->invincible) this->hp -= mob->power;
	}
}

void Player::move(const float& dt, const float dx, const float dy) {
	auto v = CustomMath::normalize(sf::Vector2f(dx, dy));
	this->cx += v.x * this->movementSpeed * dt;
	this->cy += v.y * this->movementSpeed * dt;
	//this->shape.move(dx * this->movementSpeed * dt * multiplyer, dy * this->movementSpeed * dt * multiplyer);
}

void Player::render(sf::RenderTarget* target) {
	Entity::render(target);
}

void Player::update(const float& dt, sf::Vector2f velocity) {
	this->move(dt, velocity.x, velocity.y);
	this->attack(dt);
	Entity::update(dt);
	this->bomb->update(dt, this->shape, this->cx, this->cy);
}