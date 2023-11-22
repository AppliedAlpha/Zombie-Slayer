#include "GameUI.h"

GameUI::GameUI() {
}

GameUI::GameUI(const sf::Vector2f& center) {
	updateCenterPos(center);

	hpBar[0] = sf::Vertex(centerPos + sf::Vector2f(-540, -300), sf::Color::Red);
	hpBar[1] = sf::Vertex(centerPos + sf::Vector2f(-540, -270), sf::Color::Red);
	hpBar[2] = sf::Vertex(centerPos + sf::Vector2f(540, -270), sf::Color::Red);
	hpBar[3] = sf::Vertex(centerPos + sf::Vector2f(540, -300), sf::Color::Red);

	xpBar[0] = sf::Vertex(centerPos + sf::Vector2f(-540, -260), sf::Color::Blue);
	xpBar[1] = sf::Vertex(centerPos + sf::Vector2f(-540, -250), sf::Color::Blue);
	xpBar[2] = sf::Vertex(centerPos + sf::Vector2f(540, -250), sf::Color::Blue);
	xpBar[3] = sf::Vertex(centerPos + sf::Vector2f(540, -260), sf::Color::Blue);
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

void GameUI::updateXpBar(float xp, float maxXp)
{
	float ratio = xp / maxXp * 100.f;
	xpBar[0] = sf::Vertex(centerPos + sf::Vector2f(-540, -260), sf::Color::Blue);
	xpBar[1] = sf::Vertex(centerPos + sf::Vector2f(-540, -250), sf::Color::Blue);
	xpBar[2] = sf::Vertex(centerPos + sf::Vector2f(-540 + 10.8 * ratio, -250), sf::Color::Blue);
	xpBar[3] = sf::Vertex(centerPos + sf::Vector2f(-540 + 10.8 * ratio, -260), sf::Color::Blue);
}


void GameUI::render(sf::RenderTarget* target) {
	target->draw(hpBar, 4, sf::Quads);
	target->draw(xpBar, 4, sf::Quads);
}
