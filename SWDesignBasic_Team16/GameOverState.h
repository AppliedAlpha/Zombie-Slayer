#pragma once
#include "State.h"

class GameOverState : public State {
private:
public:
	sf::Font* font;
	sf::Texture bgTexture;
	sf::Sprite bgSprite;

	GameOverState(sf::RenderWindow* window);
	virtual ~GameOverState();

	void endState();
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target);
};

