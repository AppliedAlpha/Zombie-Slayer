#pragma once
#include "State.h"

class GameOverState : public State {
private:
public:
	sf::Font* font;
	sf::Text* resultText;

	sf::Texture bgTexture;
	sf::Sprite bgSprite;

	GameOverState(sf::RenderWindow* window);
	GameOverState(sf::RenderWindow* window, const bool& allClear, const double& playTime = 0.f, const int& killCount = 0, const double& totalDamage = 0.f, const int& totalXp = 0, const int& totalGold = 0, int* weaponLevelList = nullptr);
	virtual ~GameOverState();

	void endState();
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target);
};

