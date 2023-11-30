#include "GameUI.h"

GameUI::GameUI() {
	this->font = nullptr;
}

GameUI::GameUI(const sf::Vector2f& center, sf::Font* font) {
	updateCenterPos(center);
	this->font = font;

	initColors();
	initRectPosValues();
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

	outlineGold = sf::Color(224, 160, 37, 255);
}

void GameUI::initRectPosValues() {
	hpBarRect = sf::IntRect(20, 20, 1280 - 20 * 2, 30);
	xpBarRect = sf::IntRect(20, 60, 1280 - 20 * 2, 15);
	timeTextRect = sf::IntRect(640 - 160 / 2, 85, 160, 40);
}

void GameUI::setBarPos(sf::Vertex* bar, const sf::IntRect& rect, const sf::Color& up, const sf::Color& down, const float fillPercent) {
	/* bar 작성 요령
    0 | 3
    1 | 2
    */
	bar[0] = sf::Vertex(centerPos + sf::Vector2f(-rect.width / 2, -360 + rect.top), up);
	bar[1] = sf::Vertex(centerPos + sf::Vector2f(-rect.width / 2, -360 + rect.top + rect.height), down);
	bar[2] = sf::Vertex(centerPos + sf::Vector2f(-rect.width / 2 + rect.width * (fillPercent / 100.0), -360 + rect.top + rect.height), down);
	bar[3] = sf::Vertex(centerPos + sf::Vector2f(-rect.width / 2 + rect.width * (fillPercent / 100.0), -360 + rect.top), up);
}

void GameUI::initBars() {
	setBarPos(hpBar, hpBarRect, red, bottomRed);
	setBarPos(xpBar, xpBarRect, blue, bottomBlue);

	hpBackBar.setFillColor(CustomColor::Gray(0.5f));
	hpBackBar.setSize(sf::Vector2f(hpBarRect.width, hpBarRect.height));
	hpBackBar.setPosition(centerPos + sf::Vector2f(-hpBarRect.width / 2, -360 + hpBarRect.top));
	hpBackBar.setOutlineColor(outlineGold);
	hpBackBar.setOutlineThickness(3.f);

	xpBackBar.setFillColor(CustomColor::Gray(0.5f));
	xpBackBar.setSize(sf::Vector2f(xpBarRect.width, xpBarRect.height));
	xpBackBar.setPosition(centerPos + sf::Vector2f(-xpBarRect.width / 2, -360 + xpBarRect.top));
	xpBackBar.setOutlineColor(outlineGold);
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
	timeText.setCharacterSize(48);
	timeText.setFillColor(sf::Color::White);
	timeText.setPosition(centerPos + sf::Vector2f(-timeTextRect.width / 2, -360 + timeTextRect.top));
	timeText.setString("0:00.0");
}

void GameUI::updateCenterPos(const sf::Vector2f& center) {
	this->centerPos = center;
}

void GameUI::updateHpBar(float hp, float maxHp) {
	float ratio = hp / maxHp * 100.f;

	setBarPos(hpBar, hpBarRect, red, bottomRed, ratio);
	hpBackBar.setPosition(centerPos + sf::Vector2f(-hpBarRect.width / 2, -360 + hpBarRect.top));
}

void GameUI::updateXpBar(float xp, float maxXp) {
	float ratio = xp / maxXp * 100.f;

	setBarPos(xpBar, xpBarRect, blue, bottomBlue, ratio);
	xpBackBar.setPosition(centerPos + sf::Vector2f(-xpBarRect.width / 2, -360 + xpBarRect.top));
}

void GameUI::updatePlayTimeText(float playTime) {
	int secTime = (int) playTime;
	int underSecTime = (int) (playTime * 10) % 10;
	timeText.setPosition(centerPos + sf::Vector2f(-timeTextRect.width / 2, -360 + timeTextRect.top));

	std::sprintf(timeTextBuffer, "%02d:%02d.%01d", secTime / 60, secTime % 60, underSecTime);
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
