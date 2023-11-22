#include "CustomMath.h"

// ���� ũ�� ���ϱ�
float CustomMath::getLength(const sf::Vector2f& vector)
{
	return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

// ���� ����ȭ (���� ������)
sf::Vector2f CustomMath::normalize(const sf::Vector2f& vector) {	
	float length = CustomMath::getLength(vector);
	
	if (length != 0.0f)
		return sf::Vector2f(vector.x / length, vector.y / length);
	else 
		return vector;
}