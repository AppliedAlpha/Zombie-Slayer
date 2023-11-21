#include "OptionSelectionEvent.h"

OptionSelectionEvent::OptionSelectionEvent(Player* player) : Event(player)
{
	this->options.push_back("Power 1 up");
	this->options.push_back("New Weapon: Spear");
	this->options.push_back("Weapon upgrade: Sword");
	this->initScreen();
}

OptionSelectionEvent::~OptionSelectionEvent()
{
	for (int i = 0; i < this->length; i++) {
		delete this->optionFields.at(i);
	}
	this->optionFields.clear();
}

void OptionSelectionEvent::initScreen()
{
	if (!this->font.loadFromFile("C:\\Users\\±ËªÛ¿±\\Desktop\\malgun.ttf"))
	{
		std::cout << "Cant load Font" << std::endl;
	}
	else {
		// sf::VideoMode windowBounds(1280, 720);
		float width = 1280;
		float height = 720;
		float padding = 10;
		float widthSize = (width - 2 * this->length * padding) / 3;
		float heightSize = 300;
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
			text->setPosition(padding + i * 2 * padding + i * widthSize + 50, height * 0.5 - heightSize * 0.5 + 50);
			optionTexts.push_back(text);
		}
		optionFields.at(0)->setOutlineColor(sf::Color::Red);
	}
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
	if (option == "New Weapon: Spear") {
		this->player->weaponList.push_back(new Spear(2, 2.5f, .5f));
	}
}
