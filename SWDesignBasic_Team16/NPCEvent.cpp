#include "NPCEvent.h"

NPCEvent::NPCEvent(Player* player) : Event(player)
{
	this->dialog.push_back("Hello? You are not Zombie!");
	this->dialog.push_back("Survive here if you can.");
	this->dialog.push_back("I have a present for you. Good Luck!");
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
	this->textField.setSize(sf::Vector2f(1200, 200));
	this->textField.setOutlineColor(sf::Color::White);
	this->textField.setOutlineThickness(5);
	this->textField.setFillColor(sf::Color::Black);
	this->textField.setPosition(40, 680 - 200);

	this->font.loadFromFile(this->fontDir);
	this->currentDialog.setFont(this->font);
	this->currentDialog.setPosition(80, 680 - 200 + 75);
	this->currentDialog.setString(this->dialog.front());
	this->dialog.pop_front();
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

void NPCEvent::move(sf::Vector2f diff)
{
	Event::move(diff);
	textField.move(diff);
}
