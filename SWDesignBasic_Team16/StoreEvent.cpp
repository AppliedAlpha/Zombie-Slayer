#include "StoreEvent.h"

StoreEvent::StoreEvent(Player* player) : Event(player)
{
	this->bgTexture.loadFromFile("./Resources/StoreEvent.png");
	this->bgSprite.setTexture(bgTexture);
	this->index = 0;
	this->title.setString("Stage Clear!");
	this->subtitle.setString("Press Arrow Keys to Choose a Option and Press Z to Select, X to Quit");
	this->goldText.setString("You Have " + std::to_string(player->inventory.getGold()) + " Golds");
	this->script.setString("Gold Store");
	this->options.push_back("Potion: Gold 10");
	this->options.push_back("Power Up: Gold 100");
	this->options.push_back("Max HP Up: Gold 100");
	this->options.push_back("Speed Up: Gold 100");
	this->initScreen();
}

StoreEvent::~StoreEvent()
{
	for (int i = 0; i < this->length; i++) {
		delete this->optionFields.at(i);
	}
	this->optionFields.clear();
}

void StoreEvent::initScreen()
{
	// sf::VideoMode windowBounds(1280, 720);
	float width = 1280;
	float height = 720;
	float padding = 10;
	float widthSize = (width - 2 * this->length * padding) / 4;
	float heightSize = 300;
	this->font.loadFromFile(this->fontDir);
	for (int i = 0; i < this->length; i++) {
		auto option = new sf::RectangleShape();
		option->setSize(sf::Vector2f(widthSize, heightSize));
		option->setOutlineColor(sf::Color::White);
		option->setOutlineThickness(5);
		option->setFillColor(sf::Color::Black);
		option->setPosition(padding + i * 2 * padding + i * widthSize, height * 0.5 - heightSize * 0.5);
		optionFields.push_back(option);

		auto text = new sf::Text();
		text->setFont(this->font);
		text->setString(this->options.at(i));
		auto textWidth = text->getGlobalBounds().width;
		auto textHeight = text->getGlobalBounds().height;
		text->setPosition(padding + (i * 2 * padding) + (i * widthSize) + (widthSize * 0.5 - textWidth * 0.5), height * 0.5 - textHeight * 0.5);
		optionTexts.push_back(text);
	}
	optionFields.at(0)->setOutlineColor(sf::Color::Red);
	this->title.setFont(this->font);
	this->subtitle.setFont(this->font);
	this->title.setPosition(width * 0.5 - this->title.getGlobalBounds().width * 0.5, 70);
	this->subtitle.setPosition(width * 0.5 - this->subtitle.getGlobalBounds().width * 0.5, 120);
	this->title.setFillColor(sf::Color::Yellow);
	this->goldText.setFont(this->font);
	this->goldText.setPosition(width * 0.5 - this->goldText.getGlobalBounds().width * 0.5, 600);
	this->goldText.setFillColor(sf::Color::Yellow);
	this->script.setFont(this->font);
	this->script.setPosition(width * 0.5 - this->script.getGlobalBounds().width * 0.5, 650);
}

void StoreEvent::showSelectionScreen()
{
}

void StoreEvent::update(const float& dt)
{
	for (int i = 0; i < this->length; i++) {
		if (i == this->index) this->optionFields.at(i)->setOutlineColor(sf::Color::Red);
		else this->optionFields.at(i)->setOutlineColor(sf::Color::White);
	}
}

void StoreEvent::render(sf::RenderTarget* target)
{
	target->draw(this->bgSprite);
	for (int i = 0; i < this->length; i++) {
		target->draw(*(this->optionFields.at(i)));
		target->draw(*(this->optionTexts.at(i)));
	}
	target->draw(this->title);
	target->draw(this->subtitle);
	target->draw(this->goldText);
	target->draw(this->script);
}

void StoreEvent::update(const float& dt, std::string option)
{
	auto type = option.substr(0, 3);
	int split = option.find("Gold ");
	int amount = stoi(option.substr(split + 5));
	if (this->player->inventory.getGold() < amount) {
		this->script.move(this->script.getGlobalBounds().width * 0.5, 0.f);
		this->script.setString("Not enough golds!");
		this->script.setFillColor(sf::Color::Red);
		this->script.move(-this->script.getGlobalBounds().width * 0.5, 0.f);
	}
	else {
		player->inventory.setGold(player->inventory.getGold() - amount);

		if (type == "Pot") {
			player->getPotion();
		}
		else if (type == "Pow") {
			player->power += 0.1f;
		}
		else if (type == "Max") {
			player->maxHp += 20;
			player->hp += 20;
		}
		else {
			player->movementSpeed += 10;
		}

		this->script.move(this->script.getGlobalBounds().width * 0.5, 0.f);
		this->script.setString("You bought " + option);
		this->script.setFillColor(sf::Color::White);
		this->script.move(-this->script.getGlobalBounds().width * 0.5, 0.f);
		this->goldText.setString("You Have " + std::to_string(player->inventory.getGold()) + " Golds");
	}
}

void StoreEvent::move(sf::Vector2f diff)
{
	Event::move(diff);
	this->bgSprite.move(diff);
	this->title.move(diff);
	this->subtitle.move(diff);
	this->goldText.move(diff);
	this->script.move(diff);
	for (int i = 0; i < optionFields.size(); i++) {
		optionFields.at(i)->move(diff);
		optionTexts.at(i)->move(diff);
	}
}
