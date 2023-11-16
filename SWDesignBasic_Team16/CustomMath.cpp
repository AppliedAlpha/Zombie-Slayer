#include "CustomMath.h"

// ���� ����ȭ (���� ������)
sf::Vector2f CustomMath::normalize(const sf::Vector2f& vector) {	
	float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
	
	if (length != 0.0f)
		return sf::Vector2f(vector.x / length, vector.y / length);
	else 
		return vector;
}