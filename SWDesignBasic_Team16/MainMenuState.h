#pragma once
#include "State.h"

class MainMenuState : public State {
private:
public:
	sf::Font* font;
	sf::Texture bgTexture;
	sf::Sprite bgSprite;

	MainMenuState(sf::RenderWindow* window);
	virtual ~MainMenuState();

	void endState();
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target);
};

