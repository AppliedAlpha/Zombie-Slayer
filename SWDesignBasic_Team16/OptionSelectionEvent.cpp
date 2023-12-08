#include "OptionSelectionEvent.h"

OptionSelectionEvent::OptionSelectionEvent(Player* player) : Event(player)
{
	this->bgTexture.loadFromFile("./Resources/OptionSelectionEvent.jpg");
	this->bgSprite.setTexture(bgTexture);
	selectRandomWeapon();
	this->title.setString("LEVEL UP!");
	this->subtitle.setString("Press Arrow Keys to Choose a Option and Press Z to Select!");
	this->script.setString("Max Weapon Level is 4 and Max Level Weapon is much more POWERFUL!!");
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
	this->title.setFont(this->font);
	this->subtitle.setFont(this->font);
	this->title.setPosition(width * 0.5 - this->title.getGlobalBounds().width * 0.5, 70);
	this->subtitle.setPosition(width * 0.5 - this->subtitle.getGlobalBounds().width * 0.5, 120);
	this->subtitle.setOutlineColor(sf::Color(0, 0, 0));
	this->subtitle.setOutlineThickness(1.f);
	this->title.setFillColor(sf::Color::Yellow);
	this->title.setOutlineColor(sf::Color(0, 0, 0));
	this->title.setOutlineThickness(1.f);
	this->script.setFont(this->font);
	this->script.setPosition(width * 0.5 - this->script.getGlobalBounds().width * 0.5, 650);
	this->script.setOutlineColor(sf::Color(0, 0, 0));
	this->script.setOutlineThickness(1.f);
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
	target->draw(bgSprite);
	for (int i = 0; i < this->length; i++) {
		target->draw(*(this->optionFields.at(i)));
		target->draw(*(this->optionTexts.at(i)));
	}
	target->draw(this->title);
	target->draw(this->subtitle);
	target->draw(this->script);
}

void OptionSelectionEvent::update(const float& dt, std::string option)
{
	int split = option.find(":");
	auto type = option.substr(0, split);
	if (type == "New") {
		auto weapon = option.substr(split + 2);
		int index = this->player->weaponNameToIndex(weapon);
		switch (index)
		{
		case 0:
			this->player->weaponList.insert(std::unordered_map<int, Weapon*>::value_type(index, new Sword(1, 1, .5f, sf::Vector2f(this->player->cx, this->player->cy), sf::Color::Red)));
			break;
		case 1:
			this->player->weaponList.insert(std::unordered_map<int, Weapon*>::value_type(index, new Spear(1, 1.5f, .5f, sf::Vector2f(this->player->cx, this->player->cy), sf::Color::Red)));
			break;
		case 2:
			this->player->weaponList.insert(std::unordered_map<int, Weapon*>::value_type(index, new Grinder(0, 2, 0, sf::Vector2f(this->player->cx, this->player->cy), sf::Color::Red)));
			break;
		case 3:
			this->player->weaponList.insert(std::unordered_map<int, Weapon*>::value_type(index, new Pistol(.5f, 5, 5.f, sf::Vector2f(this->player->cx, this->player->cy), 5, sf::Color::Red)));
			break;
		case 4:
			this->player->weaponList.insert(std::unordered_map<int, Weapon*>::value_type(index, new Brick(5.f, .3f, 5.f, sf::Vector2f(this->player->cx, this->player->cy), 2, sf::Color::Red)));
			break;
		case 5:
			this->player->weaponList.insert(std::unordered_map<int, Weapon*>::value_type(index, new Rocket(3.f, 0.f, 5.f, sf::Vector2f(this->player->cx, this->player->cy), 10, sf::Color::Red, 60.f, 1.f, .5f)));
			break;
		}
		int i = std::find(this->player->unselected.begin(), this->player->unselected.end(), index) - this->player->unselected.begin();
		this->player->unselected.erase(this->player->unselected.begin() + i);
		this->player->selected.push_back(index);
	}
	else if (type == "Upgrade") {
		std::string name = option.substr(split + 7);
		int index = this->player->weaponNameToIndex(name);
		auto weapon = this->player->weaponList.find(index)->second;
		if (weapon->level < weapon->maxLevel) {
			weapon->levelUp();
			if (weapon->level == weapon->maxLevel) {
				int i = std::find(this->player->selected.begin(), this->player->selected.end(), index) - this->player->selected.begin();
				this->player->selected.erase(this->player->selected.begin() + i);
			}
		}
	}
	else {
		this->player->maxHp += 60.f;
		this->player->movementSpeed += 30.f;
		this->player->power += 0.3f;
	}
}

void OptionSelectionEvent::move(sf::Vector2f diff)
{
	Event::move(diff);
	bgSprite.move(diff);
	this->title.move(diff);
	this->subtitle.move(diff);
	this->script.move(diff);
	for (int i = 0; i < optionFields.size(); i++) {
		optionFields.at(i)->move(diff);
		optionTexts.at(i)->move(diff);
	}
}

void OptionSelectionEvent::selectRandomWeapon()
{
	for (int i = 0; i < player->unselected.size(); i++)
		std::cout << player->unselected[i] << " ";
	std::cout << std::endl;
	for (int i = 0; i < player->selected.size(); i++)
		std::cout << player->selected[i] << " ";
	std::cout << std::endl;
	int option[3] = {-1, -1, -1};
	if (player->unselected.size() > 3) {
		for (;;) {
			option[0] = Random::instance().getInt(0, player->unselected.size() - 1);
			option[1] = Random::instance().getInt(0, player->unselected.size() - 1);
			option[2] = Random::instance().getInt(0, player->unselected.size() - 1);
			if (option[0] != option[1] && option[0] != option[2] && option[1] != option[2]) break;
		}
		for (int i = 0; i < 3; i++)
			this->options.push_back(this->newWeapon + player->indexToWeaponName(player->unselected.at(option[i])));
	}
	else if (player->unselected.size() > 0 && player->unselected.size() <= 3) {
		// 3
		// 2 1
		// 2 0
		// 1 2
		// 1 1
		// 1 0
		int left = 3 - player->unselected.size();
		int empty = left - player->selected.size();
		for (int i = 0; i < player->unselected.size(); i++) {
			option[i] = i;
		}
		if (player->selected.size() != 0) {
			if (empty <= 0) {
				for (;;) {
					for (int i = player->unselected.size(); i < 3; i++) {
						option[i] = Random::instance().getInt(0, player->selected.size() - 1);
					}
					if (left != 2 || (left == 2 && option[1] != option[2])) break;
				}
			}
			else {
				option[player->unselected.size()] = Random::instance().getInt(0, player->selected.size() - 1);
			}
		}
		for (int i = 0; i < player->unselected.size(); i++)
			this->options.push_back(this->newWeapon + player->indexToWeaponName(player->unselected.at(option[i])));
		for (int i = player->unselected.size(); i < 3; i++) {
			if (option[i] == -1) this->options.push_back("All Stats Up: Power, Speed, Max HP");
			else this->options.push_back(this->upgradeWeapon + +"Lv." + std::to_string(player->weaponList.find(player->selected.at(option[i]))->second->level + 1) + " " + player->indexToWeaponName(player->selected.at(option[i])));
		}
	}
	else if (player->selected.size() > 3) {
		for (;;) {
			option[0] = Random::instance().getInt(0, player->selected.size() - 1);
			option[1] = Random::instance().getInt(0, player->selected.size() - 1);
			option[2] = Random::instance().getInt(0, player->selected.size() - 1);
			if (option[0] != option[1] && option[0] != option[2] && option[1] != option[2]) break;
		}
		for (int i = 0; i < 3; i++)
			this->options.push_back(this->upgradeWeapon + "Lv." + std::to_string(player->weaponList.find(player->selected.at(option[i]))->second->level + 1) + " " + player->indexToWeaponName(player->selected.at(option[i])));
	}
	else {
		int left = 3 - player->selected.size();
		for (int i = 0; i < player->selected.size(); i++) {
			option[i] = i;
		}
		for (int i = 0; i < 3; i++) {
			if (option[i] == -1) this->options.push_back("Power Up");
			else this->options.push_back(this->upgradeWeapon + "Lv." + std::to_string(player->weaponList.find(player->selected.at(option[i]))->second->level + 1) + " " + player->indexToWeaponName(player->selected.at(option[i])));

		}
	}
}
