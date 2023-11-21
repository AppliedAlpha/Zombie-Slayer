#include "GameUI.h"

GameUI::GameUI() {
}

GameUI::GameUI(const sf::Vector2f& center) {
	updateCenterPos(center);

	hpBar[0] = sf::Vertex(centerPos + sf::Vector2f(-540, -300), sf::Color::Red);
	hpBar[1] = sf::Vertex(centerPos + sf::Vector2f(-540, -270), sf::Color::Red);
	hpBar[2] = sf::Vertex(centerPos + sf::Vector2f(540, -270), sf::Color::Red);
	hpBar[3] = sf::Vertex(centerPos + sf::Vector2f(540, -300), sf::Color::Red);
}

GameUI::~GameUI() {
}

void GameUI::updateCenterPos(const sf::Vector2f& center) {
	this->centerPos = center;
}

void GameUI::updateHpBar(float hp, float maxHp) {
	float ratio = hp / maxHp * 100.f;

	hpBar[0] = sf::Vertex(centerPos + sf::Vector2f(-540, -300), sf::Color::Red);
	hpBar[1] = sf::Vertex(centerPos + sf::Vector2f(-540, -270), sf::Color::Red);
	hpBar[2] = sf::Vertex(centerPos + sf::Vector2f(-540 + 10.8 * ratio, -270), sf::Color::Red);
	hpBar[3] = sf::Vertex(centerPos + sf::Vector2f(-540 + 10.8 * ratio, -300), sf::Color::Red);
}

void GameUI::render(sf::RenderTarget* target) {
	target->draw(hpBar, 4, sf::Quads);
}
