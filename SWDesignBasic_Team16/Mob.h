#pragma once
#include "Entity.h"
#include "Sword.h"

class Mob : public Entity
{
private:
	void initShape();
public:
	void updateCollision(Sword* sword);
	Mob();
	~Mob();
};