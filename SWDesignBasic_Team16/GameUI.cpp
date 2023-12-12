#include "GameUI.h"

GameUI::GameUI() {
	this->font = nullptr;
}

GameUI::GameUI(const sf::Vector2f& center, sf::Font* font, sf::Texture* texture) {
	updateCenterPos(center);
	diff = sf::Vector2f(640, 360);
	this->font = font;

	this->allTextures = texture;
	for (int i=0; i<3; i++)
		this->itemSprite[i] = sf::Sprite(*this->allTextures, sf::IntRect(540, i * 60, 60, 60));
	for (int i=0; i<6; i++) {
		this->weaponSprite[i] = sf::Sprite(*this->allTextures);
		this->weaponSprite[i].setTextureRect(sf::IntRect(i * 60, 540, 60, 60));
	}
		
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
	levelTextPos = sf::Vector2f(1095, 85);
	stageTextPos = sf::Vector2f(1148, 115);

	for (int i = 0; i < 3; i++) {
		itemCountTextPos[i][0] = sf::Vector2f(210 + 44 + i * 80, 675);
		itemCountTextPos[i][1] = sf::Vector2f(210 + 41 + i * 80, 680);
	}

	for (int i = 0; i < 6; i++)
		weaponLevelTextPos[i] = sf::Vector2f(740 + i * 80, 613);
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

	for (int i = 0; i < 3; i++) {
		itemSlotCoolBar[i][0] = sf::Vertex(centerPos - diff + sf::Vector2f(210 + i * 80, 640), itemCoolBarColor);
		itemSlotCoolBar[i][1] = sf::Vertex(centerPos - diff + sf::Vector2f(210 + i * 80, 700), itemCoolBarColor);
		itemSlotCoolBar[i][2] = sf::Vertex(centerPos - diff + sf::Vector2f(270 + i * 80, 700), itemCoolBarColor);
		itemSlotCoolBar[i][3] = sf::Vertex(centerPos - diff + sf::Vector2f(270 + i * 80, 640), itemCoolBarColor);
	}
}

void GameUI::initTexts() {
	levelText.setFont(*font);
	levelText.setCharacterSize(24);
	levelText.setFillColor(sf::Color::White);
	levelText.setPosition(centerPos - diff + levelTextPos);
	levelText.setString("Player Level 1");

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

	for (int i = 0; i < 3; i++) {
		itemCountText[i].setFont(*font);
		itemCountText[i].setCharacterSize(20);
		itemCountText[i].setFillColor(sf::Color::Black);
		itemCountText[i].setOutlineColor(sf::Color::White);
		itemCountText[i].setPosition(centerPos - diff + itemCountTextPos[i][0]);
		itemCountText[i].setString("0");
	}

	for (int i = 0; i < 6; i++) {
		weaponLevelText[i].setFont(*font);
		weaponLevelText[i].setCharacterSize(20);
		weaponLevelText[i].setFillColor(sf::Color::White);
		weaponLevelText[i].setPosition(centerPos - diff + weaponLevelTextPos[i]);
		weaponLevelText[i].setString("");
	}
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

void GameUI::updateItemSlot(float coolDown[], int potionCount, int bombCount, int iceCount) {
	for (int i = 0; i < 3; i++) {
		itemSlotCoolBar[i][0] = sf::Vertex(centerPos - diff + sf::Vector2f(210 + i * 80, 700 - coolDown[i] * 60), itemCoolBarColor);
		itemSlotCoolBar[i][1] = sf::Vertex(centerPos - diff + sf::Vector2f(210 + i * 80, 700), itemCoolBarColor);
		itemSlotCoolBar[i][2] = sf::Vertex(centerPos - diff + sf::Vector2f(270 + i * 80, 700), itemCoolBarColor);
		itemSlotCoolBar[i][3] = sf::Vertex(centerPos - diff + sf::Vector2f(270 + i * 80, 700 - coolDown[i] * 60), itemCoolBarColor);

		this->itemSprite[i].setPosition(centerPos - diff + sf::Vector2f(210 + i * 80, 640));

		if (i == 0) {
			this->itemCountText[i].setCharacterSize(potionCount >= 10 ? 14 : 20);
			this->itemCountText[i].setString(std::to_string(potionCount));
			this->itemCountText[i].setPosition(centerPos - diff + itemCountTextPos[i][potionCount >= 10]);
		}
		else if (i == 1) {
			this->itemCountText[i].setCharacterSize(bombCount >= 10 ? 14 : 20);
			this->itemCountText[i].setString(std::to_string(bombCount));
			this->itemCountText[i].setPosition(centerPos - diff + itemCountTextPos[i][bombCount >= 10]);
		}
		else {
			this->itemCountText[i].setCharacterSize(iceCount >= 10 ? 14 : 20);
			this->itemCountText[i].setString(std::to_string(iceCount));
			this->itemCountText[i].setPosition(centerPos - diff + itemCountTextPos[i][iceCount >= 10]);
		}
	}
}

void GameUI::updateWeaponSlot(int* weaponLevel) {
	for (int i = 0; i < 6; i++) {
		if (weaponLevel[i] == 0) {
			this->weaponSprite[i].setTextureRect(sf::IntRect(360, 540, 60, 60));
			this->weaponLevelText[i].setString("");
		}
		else {
			this->weaponSprite[i].setTextureRect(sf::IntRect(i * 60, 540, 60, 60));
			this->weaponLevelText[i].setString("LV " + std::to_string(weaponLevel[i]));
		}

		this->weaponSprite[i].setPosition(centerPos - diff + sf::Vector2f(730 + i * 80, 640));
		this->weaponLevelText[i].setPosition(centerPos - diff + weaponLevelTextPos[i]);
	}
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
	levelText.setString("Player Level " + std::to_string(level));
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
	
	for (int i = 0; i < 3; i++) {
		target->draw(itemSprite[i]);
		target->draw(itemCountText[i]);
	
		target->draw(itemSlotCoolBar[i], 4, sf::Quads);
	}

	for (int i = 0; i < 6; i++) {
		target->draw(weaponSprite[i]);
		target->draw(weaponLevelText[i]);
	}

	// render bars
	target->draw(hpBar, 4, sf::Quads);
	target->draw(xpBar, 4, sf::Quads);

	// render texts
	target->draw(levelText);
	target->draw(goldText);
	target->draw(timeText);
	target->draw(stageText);
}
