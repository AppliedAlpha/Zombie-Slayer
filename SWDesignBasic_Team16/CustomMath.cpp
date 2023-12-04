#include "Random.h"
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

// 반지름이 R일 때 원 둘레 상에 있는 랜덤한 점 좌표 반환
std::pair<float, float> CustomMath::getRandomCoordWithRadius(const float& r) {
	float angle = Random::instance().getFloat(0, 360);
	float angleRad = angle * 3.141592f / 180.f;

	return std::pair<float, float>(r * cos(angleRad), r * sin(angleRad));
}

// 레벨에 맞는 최대 xp 반환
// 경험치 조정이 필요하면 해당 식 수정
int CustomMath::getMaxXp(const int level)
{
	return level * (level + 20);
}
