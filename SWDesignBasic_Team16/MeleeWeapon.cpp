#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(float cooltime, float damage, float duration) : Weapon(cooltime, damage, duration)
{
}

MeleeWeapon::~MeleeWeapon()
{
}

void MeleeWeapon::initShape()
{
}

void MeleeWeapon::updateCollision(Entity* object)
{
}

void MeleeWeapon::update(const float& dt, sf::RectangleShape playerShape, float cx, float cy, float angle)
{
	Weapon::update(dt, playerShape, cx, cy, angle);
}

void MeleeWeapon::render(sf::RenderTarget* target)
{
}
