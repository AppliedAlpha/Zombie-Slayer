#include "NPCEvent.h"

NPCEvent::NPCEvent(Player* player) : Event(player)
{
	this->dialog.push_back("Hello?");
	this->dialog.push_back("You are alive!");
	this->dialog.push_back("I have a present for you.");
	this->dialog.push_back("You got 10 golds.");
	initScreen();
}

NPCEvent::~NPCEvent()
{
	this->player->inventory.setGold(this->player->inventory.getGold() + 10);
	std::cout << "Your Golds: " << this->player->inventory.getGold() << std::endl;
}

void NPCEvent::initScreen()
{
	// sf::VideoMode windowBounds(1280, 720);
	this->textField.setSize(sf::Vector2f(1280, 300));
	this->textField.setFillColor(sf::Color::Black);
	this->textField.setPosition(0, 720 - 300);
	this->currentDialog.setPosition(30, 720 - 300 + 150);
	if (!this->font.loadFromFile("C:\\Users\\�����\\Desktop\\malgun.ttf"))
	{
		std::cout << "Cant load Font" << std::endl;
	}
	else {
		this->currentDialog.setFont(this->font);
		this->currentDialog.setString(this->dialog.front());
		this->dialog.pop_front();
	}
}

void NPCEvent::showSelectionScreen()
{
}

void NPCEvent::update(const float& dt)
{
	this->currentDialog.setString(this->dialog.front());
	this->dialog.pop_front();
}

void NPCEvent::render(sf::RenderTarget* target)
{
	target->draw(this->textField);
	target->draw(this->currentDialog);
}
