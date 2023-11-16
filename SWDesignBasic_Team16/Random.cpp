#include "Random.h"

Random* Random::_instance = nullptr;

Random::Random() : gen(new std::mt19937(rd())) {}

Random::~Random() {
	delete gen;
}

int Random::getInt(int min, int max)
{
	std::uniform_int_distribution<int> dis(min, max);
	return dis(*gen);
}

float Random::getFloat(float min = 0.f, float max = 1.f)
{
	std::uniform_real_distribution<float> dis(min, max);
	return dis(*gen);
}
