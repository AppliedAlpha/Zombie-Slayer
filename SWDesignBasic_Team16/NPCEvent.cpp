#include "NPCEvent.h"

NPCEvent::NPCEvent(Player* player, int level, std::deque<std::string>& dialog, std::string npc, int& npcEvent, int positive) : Event(player), dialog(dialog), npcEvent(npcEvent)
{
	this->bgTexture.loadFromFile("./Resources/NpcEvent.png");
	this->bgSprite.setTexture(bgTexture);
	initScreen();
	this->level = level;
	this->title.setString(npc);
	this->subtitle.setString("Press Z");
	this->positive = positive;
}

NPCEvent::~NPCEvent()
{
	this->npcEvent = this->positive;
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

	this->title.setFont(this->font);
	this->title.setPosition(80, 680 - 180);
	this->title.setFillColor(sf::Color::Yellow);

	this->subtitle.setFont(this->font);
	this->subtitle.setPosition(1100, 680 - 50);
}

void NPCEvent::showSelectionScreen()
{
};

void NPCEvent::update(const float& dt)
{
	this->currentDialog.setString(this->dialog.front());
	this->dialog.pop_front();
}

void NPCEvent::render(sf::RenderTarget* target)
{
	target->draw(bgSprite);
	target->draw(this->textField);
	target->draw(this->currentDialog);
	target->draw(this->title);
	target->draw(this->subtitle);
}

void NPCEvent::move(sf::Vector2f diff)
{
	Event::move(diff);
	bgSprite.move(diff);
	textField.move(diff);
	currentDialog.move(diff);
	title.move(diff);
	subtitle.move(diff);
}
