#include "CustomMath.h"

// 벡터 크기 구하기
float CustomMath::getLength(const sf::Vector2f& vector)
{
	return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

// 벡터 정규화 (방향 정보만)
sf::Vector2f CustomMath::normalize(const sf::Vector2f& vector) {	
	float length = CustomMath::getLength(vector);
	
	if (length != 0.0f)
		return sf::Vector2f(vector.x / length, vector.y / length);
	else 
		return vector;
}