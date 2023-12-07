#pragma once
#include "MeleeWeapon.h"
class Grinder : public MeleeWeapon
{
private:
public:
	int rotation;
	int rotationSpeed;
	Grinder(float cooltime, float damage, float duration, sf::Vector2f position, sf::Color color);
	~Grinder();
	void initShape();
	void updateCollision(Entity* object);
	void update(const float& dt, sf::RectangleShape playerShape, float cx, float cy, sf::Vector2f viewDirection);
	void render(sf::RenderTarget* target);
	void levelUp();
};

