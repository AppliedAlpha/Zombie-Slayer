#include "OptionSelectionEvent.h"

OptionSelectionEvent::OptionSelectionEvent(Player* player) : Event(player)
{
	this->options.push_back("New Weapon: Grinder");
	this->options.push_back("New Weapon: Spear");
	this->options.push_back("Weapon Upgrade: Sword");
	this->initScreen();
}

OptionSelectionEvent::~OptionSelectionEvent()
{
	this->player->hp = this->player->maxHp;
	for (int i = 0; i < this->length; i++) {
		delete this->optionFields.at(i);
	}
	this->optionFields.clear();
}

void OptionSelectionEvent::initScreen()
{
	// sf::VideoMode windowBounds(1280, 720);
	float width = 1280;
	float height = 720;
	float padding = 10;
	float widthSize = (width - 2 * this->length * padding) / 3;
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
}

void OptionSelectionEvent::showSelectionScreen()
{
}

void OptionSelectionEvent::update(const float& dt)
{
	for (int i = 0; i < this->length; i++) {
		if (i == this->index) this->optionFields.at(i)->setOutlineColor(sf::Color::Red);
		else this->optionFields.at(i)->setOutlineColor(sf::Color::White);
	}
}

void OptionSelectionEvent::render(sf::RenderTarget* target)
{
	for (int i = 0; i < this->length; i++) {
		target->draw(*(this->optionFields.at(i)));
		target->draw(*(this->optionTexts.at(i)));
	}
}

void OptionSelectionEvent::update(const float& dt, std::string option)
{
	if (option == "New Weapon: Grinder") {
		this->player->weaponList.insert(std::unordered_map<std::string, Weapon*>::value_type("Grinder", new Grinder(0, 1, 0)));
	}
	else if (option == "New Weapon: Spear") {
		this->player->weaponList.insert(std::unordered_map<std::string, Weapon*>::value_type("Spear", new Spear(2, 2.5f, .25f)));
	}
	else if (option == "Weapon Upgrade: Sword") {
		auto sword = this->player->weaponList.find("Sword");
		sword->second->cooltime -= 0.5;
		sword->second->damage += 1;
	}
}
