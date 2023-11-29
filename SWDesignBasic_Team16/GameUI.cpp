#include "GameUI.h"

GameUI::GameUI() {
	this->font = nullptr;
}

GameUI::GameUI(const sf::Vector2f& center, sf::Font* font) {
	updateCenterPos(center);
	this->font = font;

	initColors();
	initBars();
	initTexts();
}

GameUI::~GameUI() {
}

void GameUI::initColors() {
	red = sf::Color::Red;
	blue = sf::Color(34, 101, 221, 255);

	bottomRed = sf::Color(127, 0, 0, 255);
	bottomBlue = sf::Color(17, 50, 255, 255);
}

void GameUI::initBars() {
	/* bar 작성 요령
	   0 | 3
	   1 | 2
	*/
	hpBar[0] = sf::Vertex(centerPos + sf::Vector2f(-540, -300), red);
	hpBar[1] = sf::Vertex(centerPos + sf::Vector2f(-540, -270), bottomRed);
	hpBar[2] = sf::Vertex(centerPos + sf::Vector2f(540, -270), bottomRed);
	hpBar[3] = sf::Vertex(centerPos + sf::Vector2f(540, -300), red);

	xpBar[0] = sf::Vertex(centerPos + sf::Vector2f(-540, -260), blue);
	xpBar[1] = sf::Vertex(centerPos + sf::Vector2f(-540, -245), bottomBlue);
	xpBar[2] = sf::Vertex(centerPos + sf::Vector2f(540, -245), bottomBlue);
	xpBar[3] = sf::Vertex(centerPos + sf::Vector2f(540, -260), blue);

	hpBackBar.setFillColor(sf::Color(63, 63, 63, 255));
	hpBackBar.setSize(sf::Vector2f(1080, 30));
	hpBackBar.setPosition(centerPos + sf::Vector2f(-540, -300));
	hpBackBar.setOutlineColor(sf::Color(224, 160, 37, 255));
	hpBackBar.setOutlineThickness(3.f);

	xpBackBar.setFillColor(sf::Color(127, 127, 127, 255));
	xpBackBar.setSize(sf::Vector2f(1080, 15));
	xpBackBar.setPosition(centerPos + sf::Vector2f(-540, -260));
	xpBackBar.setOutlineColor(sf::Color(224, 160, 37, 255));
	xpBackBar.setOutlineThickness(2.f);
}

void GameUI::initTexts() {
	levelText.setFont(*font);
	levelText.setCharacterSize(20);
	levelText.setFillColor(sf::Color::White);
	levelText.setPosition(-620.f + centerPos.x, -360.f + centerPos.y);
	levelText.setString("Level: 1");

	goldText.setFont(*font);
	goldText.setCharacterSize(20);
	goldText.setFillColor(sf::Color::Yellow);
	goldText.setPosition(-620.f + centerPos.x, -340.f + centerPos.y);
	goldText.setString("Gold: 0");

	timeText.setFont(*font);
	timeText.setCharacterSize(20);
	timeText.setFillColor(sf::Color::White);
	timeText.setPosition(-620.f + centerPos.x, -320.f + centerPos.y);
	timeText.setString("0:00.00");
}

void GameUI::updateCenterPos(const sf::Vector2f& center) {
	this->centerPos = center;
}

void GameUI::updateHpBar(float hp, float maxHp) {
	float ratio = hp / maxHp * 100.f;

	hpBar[0] = sf::Vertex(centerPos + sf::Vector2f(-540, -300), red);
	hpBar[1] = sf::Vertex(centerPos + sf::Vector2f(-540, -270), bottomRed);
	hpBar[2] = sf::Vertex(centerPos + sf::Vector2f(-540 + 10.8 * ratio, -270), bottomRed);
	hpBar[3] = sf::Vertex(centerPos + sf::Vector2f(-540 + 10.8 * ratio, -300), red);

	hpBackBar.setPosition(centerPos + sf::Vector2f(-540, -300));
}

void GameUI::updateXpBar(float xp, float maxXp)
{
	float ratio = xp / maxXp * 100.f;
	xpBar[0] = sf::Vertex(centerPos + sf::Vector2f(-540, -260), blue);
	xpBar[1] = sf::Vertex(centerPos + sf::Vector2f(-540, -245), bottomBlue);
	xpBar[2] = sf::Vertex(centerPos + sf::Vector2f(-540 + 10.8 * ratio, -245), bottomBlue);
	xpBar[3] = sf::Vertex(centerPos + sf::Vector2f(-540 + 10.8 * ratio, -260), blue);

	xpBackBar.setPosition(centerPos + sf::Vector2f(-540, -260));
}

void GameUI::updatePlayTimeText(float playTime) {
	int secTime = (int) playTime;
	int underSecTime = (int) (playTime * 100) % 100;
	timeText.setPosition(-620.f + centerPos.x, -320.f + centerPos.y);

	std::sprintf(timeTextBuffer, "%d:%02d.%02d", secTime / 60, secTime % 60, underSecTime);
	timeText.setString(std::string(timeTextBuffer));
}

void GameUI::updateLevelText(int level) {
	levelText.setPosition(-620.f + centerPos.x, -360.f + centerPos.y);
	levelText.setString("Level: " + std::to_string(level));
}

void GameUI::updateGoldText(int gold) {
	goldText.setPosition(-620.f + centerPos.x, -340.f + centerPos.y);
	goldText.setString("Gold: " + std::to_string(gold));
}


void GameUI::render(sf::RenderTarget* target) {
	// 코드 뒤쪽에 있을수록 상단에 그려짐.
	// render back bars
	target->draw(hpBackBar);
	target->draw(xpBackBar);

	// render bars
	target->draw(hpBar, 4, sf::Quads);
	target->draw(xpBar, 4, sf::Quads);

	// render texts
	target->draw(levelText);
	target->draw(goldText);
	target->draw(timeText);
}
