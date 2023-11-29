#include "GameManager.h"

void GameManager::initWindow() {
	std::ifstream ifs("Config/window.ini");

	std::string title;
	sf::VideoMode windowBounds(1280, 720);
	unsigned int frameRateLimit = 60;
	bool verticalSyncEnabled = false;

	if (ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> windowBounds.width >> windowBounds.height;
		ifs >> frameRateLimit;
		ifs >> verticalSyncEnabled;
	}

	ifs.close();

	this->window = new sf::RenderWindow(windowBounds, title);
	this->window->setFramerateLimit(frameRateLimit);
	this->window->setVerticalSyncEnabled(verticalSyncEnabled);
}

void GameManager::initStates() {
	this->states.push_front(new MainMenuState(this->window));
}

GameManager::GameManager() {
	this->initWindow();
	this->initStates();
}

GameManager::~GameManager() {
	delete this->window;

	while (!this->states.empty()) {
		delete this->states.front();
		this->states.pop_front();
	}
}

template <typename CurrentState, typename NextState>
void GameManager::transitionStates(bool autoTransit) {
	if (CurrentState* p = dynamic_cast<CurrentState *>(this->states.front())) {
		if (autoTransit) {
			this->states.push_back(new NextState(this->window));
			return;
		}

		switch (this->states.front()->getExitCode()) {
		case ExitCode::NEXT:
			this->states.push_back(new NextState(this->window));
			break;

		default:
			break;
		}
	}
}

void GameManager::endGame() {
	std::cout << "Ending Game\n";
}

void GameManager::pushStates(std::deque<Event*>& eventQueue, sf::View& view)
{
	while (!eventQueue.empty()) {
		this->states.push_front(new EventState(this->window, view, eventQueue.front()));
		eventQueue.pop_front();
	}
}

void GameManager::updateDt() {
	this->dt = this->dtClock.restart().asSeconds();
}

void GameManager::updateSFMLEvents() {
	while (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed)
			this->window->close();
	}
}

void GameManager::update() {
	this->updateSFMLEvents();
	
	if (!this->states.empty()) {
		if (!this->states.front()->eventQueue.empty()) {
			pushStates(this->states.front()->eventQueue, this->states.front()->view);
			this->states.front()->eventQueue.clear();
		}
		this->states.front()->update(this->dt);

		if (this->states.front()->getQuit()) {
			this->states.front()->endState();

			// 기존 state 종료 시 새로운 state를 뒤에 밀어넣는 작업
			this->transitionStates<MainMenuState, GameState>(false);
			this->transitionStates<GameState, GameOverState>(true);
			this->transitionStates<GameOverState, MainMenuState>(false);

			delete this->states.front();
			this->states.pop_front();
		}
		
	}
	else {
		this->endGame();
		this->window->close();
	}
}

void GameManager::render() {
	this->window->clear();

	if (!this->states.empty())
		this->states.front()->render(this->window);

	this->window->display();
}

void GameManager::run() {
	while (this->window->isOpen()) {
		this->updateDt();
		this->update();
		this->render();
	}
}
