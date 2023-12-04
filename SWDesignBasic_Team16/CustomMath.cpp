#include "Random.h"
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

// �������� R�� �� �� �ѷ� �� �ִ� ������ �� ��ǥ ��ȯ
std::pair<float, float> CustomMath::getRandomCoordWithRadius(const float& r) {
	float angle = Random::instance().getFloat(0, 360);
	float angleRad = angle * 3.141592f / 180.f;

	return std::pair<float, float>(r * cos(angleRad), r * sin(angleRad));
}

// ������ �´� �ִ� xp ��ȯ
// ����ġ ������ �ʿ��ϸ� �ش� �� ����
int CustomMath::getMaxXp(const int level)
{
	return level * (level + 20);
}
