#include "GameUI.h"

GameUI::GameUI() {
	this->font = nullptr;
}

GameUI::GameUI(const sf::Vector2f& center, sf::Font* font, sf::Texture* texture) {
	updateCenterPos(center);
	diff = sf::Vector2f(640, 360);
	this->font = font;

	this->allTextures = texture;
	this->itemPotion = sf::Sprite(*this->allTextures, sf::IntRect(540, 0, 60, 60));
		
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
	itemCoolBarColor = sf::Color(31, 31, 31, 127);
}

void GameUI::initRectPosValues() {
	hpBarRect = sf::IntRect(20, 20, 1280 - 20 * 2, 30);
	xpBarRect = sf::IntRect(20, 60, 1280 - 20 * 2, 15);

	timeTextPos = sf::Vector2f(640 - 160 / 2, 80);
	goldTextPos = sf::Vector2f(20, 85);
	levelTextPos = sf::Vector2f(1166, 85);
	stageTextPos = sf::Vector2f(1160, 670);

	itemPotionCountTextPos[0] = sf::Vector2f(64, 675);
	itemPotionCountTextPos[1] = sf::Vector2f(61, 680);
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

	for (int i = 0; i < 1; i++) {
		itemSlot[i].setFillColor(sf::Color::White);
		itemSlot[i].setSize(sf::Vector2f(60, 60));
		itemSlot[i].setPosition(centerPos + sf::Vector2f(-620 + i * 70, 280));
		itemSlot[i].setOutlineColor(CustomColor::Gray(0.1f));
		itemSlot[i].setOutlineThickness(2.f);
	}

	itemSlotCoolBar[0][0] = sf::Vertex(centerPos + sf::Vector2f(-620, 280), itemCoolBarColor);
	itemSlotCoolBar[0][1] = sf::Vertex(centerPos + sf::Vector2f(-620, 340), itemCoolBarColor);
	itemSlotCoolBar[0][2] = sf::Vertex(centerPos + sf::Vector2f(-560, 340), itemCoolBarColor);
	itemSlotCoolBar[0][3] = sf::Vertex(centerPos + sf::Vector2f(-560, 280), itemCoolBarColor);
}

void GameUI::initTexts() {
	levelText.setFont(*font);
	levelText.setCharacterSize(24);
	levelText.setFillColor(sf::Color::White);
	levelText.setPosition(centerPos - diff + levelTextPos);
	levelText.setString("Level 1");

	goldText.setFont(*font);
	goldText.setCharacterSize(24);
	goldText.setFillColor(sf::Color::Yellow);
	goldText.setPosition(centerPos - diff + goldTextPos);
	goldText.setString("Gold: 0");

	stageText.setFont(*font);
	stageText.setCharacterSize(30);
	stageText.setFillColor(sf::Color::White);
	stageText.setPosition(centerPos - diff + stageTextPos);
	stageText.setString("Stage 1");

	timeText.setFont(*font);
	timeText.setCharacterSize(48);
	timeText.setFillColor(sf::Color::White);
	timeText.setPosition(centerPos - diff + timeTextPos);
	timeText.setString("0:00.0");

	itemPotionCountText.setFont(*font);
	itemPotionCountText.setCharacterSize(20);
	itemPotionCountText.setFillColor(sf::Color::Black);
	itemPotionCountText.setOutlineColor(sf::Color::White);
	itemPotionCountText.setPosition(centerPos - diff + itemPotionCountTextPos[0]);
	itemPotionCountText.setString("0");
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

void GameUI::updateItemSlot(float coolDown, int potionCount) {
	itemSlotCoolBar[0][0] = sf::Vertex(centerPos + sf::Vector2f(-620, 340 - 60 * coolDown), itemCoolBarColor);
	itemSlotCoolBar[0][1] = sf::Vertex(centerPos + sf::Vector2f(-620, 340), itemCoolBarColor);
	itemSlotCoolBar[0][2] = sf::Vertex(centerPos + sf::Vector2f(-560, 340), itemCoolBarColor);
	itemSlotCoolBar[0][3] = sf::Vertex(centerPos + sf::Vector2f(-560, 340 - 60 * coolDown), itemCoolBarColor);

	for (int i = 0; i < 1; i++) {
		itemSlot[i].setPosition(centerPos + sf::Vector2f(-620 + i * 70, 280));
	}

	this->itemPotion.setPosition(centerPos + sf::Vector2f(-620, 280));

	this->itemPotionCountText.setCharacterSize(potionCount >= 10 ? 14 : 20);
	this->itemPotionCountText.setString(std::to_string(potionCount));
	this->itemPotionCountText.setPosition(centerPos - diff + itemPotionCountTextPos[potionCount >= 10]);
}

void GameUI::updatePlayTimeText(float playTime) {
	int secTime = (int) playTime;
	int underSecTime = (int) (playTime * 10) % 10;
	timeText.setPosition(centerPos - diff + timeTextPos);

	std::sprintf(timeTextBuffer, "%02d:%02d.%01d", secTime / 60, secTime % 60, underSecTime);
	timeText.setString(std::string(timeTextBuffer));
}

void GameUI::updateLevelText(int level) {
	levelText.setPosition(centerPos - diff + levelTextPos);
	levelText.setString("Level " + std::to_string(level));
}

void GameUI::updateGoldText(int gold) {
	goldText.setPosition(centerPos - diff + goldTextPos);
	goldText.setString("Gold: " + std::to_string(gold));
}

void GameUI::updateStageText(int stage) {
	stageText.setPosition(centerPos - diff + stageTextPos);
	stageText.setString("Stage " + std::to_string(stage));
}


void GameUI::render(sf::RenderTarget* target) {
	// 코드 뒤쪽에 있을수록 상단에 그려짐.
	// render back bars
	target->draw(hpBackBar);
	target->draw(xpBackBar);
	
	// for (int i = 0; i < 1; i++)
	//	target->draw(itemSlot[i]);
	target->draw(itemPotion);
	target->draw(itemPotionCountText);

	target->draw(itemSlotCoolBar[0], 4, sf::Quads);

	// render bars
	target->draw(hpBar, 4, sf::Quads);
	target->draw(xpBar, 4, sf::Quads);

	// render texts
	target->draw(levelText);
	target->draw(goldText);
	target->draw(timeText);
	target->draw(stageText);
}
