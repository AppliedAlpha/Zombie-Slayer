#pragma once
#include <random>

class Random
{
private:
	Random();
	~Random();

	static Random* _instance;

	std::random_device rd;
	std::mt19937* gen;

public:
	static Random& instance() {
		if (_instance == nullptr) {
			_instance = new Random();
		}

		return *_instance;
	}

	int getInt(int min, int max);
	float getFloat(float min, float max);

	bool eventOccursWithProbability(float probability);

};