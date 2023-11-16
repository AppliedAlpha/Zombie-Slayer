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
	this->shape.setSize(sf::Vector2f(this->girdSize, this->girdSize));
	this->shape.setFillColor(sf::Color::White);
	
	this->shape.setOrigin(sf::Vector2f(this->shape.getLocalBounds().width, this->shape.getLocalBounds().height) / 2.f);
	this->shape.setPosition(this->shape.getPosition().x + this->shape.getOrigin().x, this->shape.getPosition().y + this->shape.getOrigin().y);
	
	this->shape.setRotation(45);
}

Player::Player() : Entity(10, 5, 100)
{
	this->initShape();
	this->initVariables();

	// TODO: 맨 처음에 무기 구석에 있는 거 고치기
	this->sword = new Sword(1, 1, .5f);
}

Player::~Player()
{
	delete this->sword;
}

void Player::attack()
{
}

void Player::updateCollision(Entity* object, sf::Vector2f& velocity)
{
	this->hp -= object->power;
	if (this->hp <= 0.f) {
		printf("You Died\n");
		this->death = true;
	}
	else {
		printf("Player: %.1f\n", this->hp);
	}
	//// 아래 충돌
	//sf::FloatRect playerBounds = this->nextPos;
	//sf::FloatRect objectBounds = object->getShape().getGlobalBounds();
	//if (playerBounds.top < objectBounds.top &&
	//	playerBounds.top + playerBounds.height < objectBounds.top + objectBounds.height &&
	//	playerBounds.left < objectBounds.left + objectBounds.width &&
	//	playerBounds.left + playerBounds.width > objectBounds.left) {
	//	velocity.y = 0.f;
	//	this->cy = this->cy - (playerBounds.top + playerBounds.height - objectBounds.top);
	//	// this->shape.setPosition(playerBounds.left, objectBounds.top - playerBounds.height);
	//}
	//// 위 충돌
	//else if (playerBounds.top > objectBounds.top &&
	//	playerBounds.top + playerBounds.height > objectBounds.top + objectBounds.height &&
	//	playerBounds.left < objectBounds.left + objectBounds.width &&
	//	playerBounds.left + playerBounds.width > objectBounds.left) {
	//	velocity.y = 0.f;
	//	this->cy = this->cy + (objectBounds.top + objectBounds.height - playerBounds.top);
	//	// this->shape.setPosition(this->shape.getGlobalBounds().left, object->downside);
	//}
	//// 오른쪽 충돌
	//if (playerBounds.left < objectBounds.left &&
	//	playerBounds.left + playerBounds.width < objectBounds.left + objectBounds.width &&
	//	playerBounds.top < objectBounds.top + objectBounds.height &&
	//	playerBounds.top + playerBounds.height > objectBounds.top) {
	//	velocity.x = 0.f;
	//	this->cx = this->cx - (playerBounds.left + playerBounds.width - objectBounds.left);
	//	// this->shape.setPosition(object->leftside - playerBounds.width, playerBounds.top);
	//}
	//// 왼쪽 충돌
	//else if (playerBounds.left > objectBounds.left &&
	//	playerBounds.left + playerBounds.width > objectBounds.left + objectBounds.width &&
	//	playerBounds.top < objectBounds.top + objectBounds.height &&
	//	playerBounds.top + playerBounds.height > objectBounds.top) {
	//	velocity.x = 0.f;
	//	this->cx = this->cx + (objectBounds.left + objectBounds.width - playerBounds.left);
	//	// this->shape.setPosition(object->rightside, playerBounds.top);
	//}
}

void Player::move(const float& dt, const float dx, const float dy) {
	float multiplyer = 20.f;
	this->cx += dx * this->movementSpeed * dt * multiplyer;
	this->cy += dy * this->movementSpeed * dt * multiplyer;
	//this->shape.move(dx * this->movementSpeed * dt * multiplyer, dy * this->movementSpeed * dt * multiplyer);
}

void Player::render(sf::RenderTarget* target) {
	Entity::render(target);
}

float Player::getViewAngle()
{
	float angle = 0.f;
	if (this->viewDirection.x == 0.f && this->viewDirection.y == 1.f) {
		angle = 45.f;
	}
	else if (this->viewDirection.x == -1.f && this->viewDirection.y == 1.f) {
		angle = 90.f;
	}
	else if (this->viewDirection.x == -1.f && this->viewDirection.y == 0.f) {
		angle = 135.f;
	}
	else if (this->viewDirection.x == -1.f && this->viewDirection.y == -1.f) {
		angle = 180.f;
	}
	else if (this->viewDirection.x == 0.f && this->viewDirection.y == -1.f) {
		angle = 225.f;
	}
	else if (this->viewDirection.x == 1.f && this->viewDirection.y == -1.f) {
		angle = 270.f;
	}
	else if (this->viewDirection.x == 1.f && this->viewDirection.y == 0.f) {
		angle = 315.f;
	}
	else if (this->viewDirection.x == 1.f && this->viewDirection.y == 1.f) {
		angle = 360.f;
	}
	return angle;
}

void Player::update(const float& dt, sf::Vector2f velocity) {
	float angle = getViewAngle();
	this->move(dt, velocity.x, velocity.y);
	this->sword->update(dt, this->shape, this->cx, this->cy, angle);
}