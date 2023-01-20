// Game.cpp
// Ethan Kerr


#include "Entity.h"
#include "Glider.h"
#include "Game.h"

// constructors
Game::Game() {
	this->initVariables();
	this->initWindow();
    this->initScene();
}

Game::~Game() {
	delete this->window;
}

// functions

void Game::pollEvents() {
    // event handlers
    while (this->window->pollEvent(this->event)) {
        switch (this->event.type) {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape) {
                this->window->close();
                break;
            }
        }
    }
}

void Game::update() {

    // poll for events
    this->pollEvents();

    for (Entity* e: entities) {
        e->update(this);
    }
}

void Game::render() {
    this->window->clear(sf::Color(40, 40, 35, 255)); // clear window

    // draw game objects
    for (Entity* e: entities) {
        e->draw(this);
    }

    this->window->display(); // display window
}

// private helper functions
void Game::initVariables() {
	this->window = nullptr;
    this->videoMode = sf::VideoMode(1200, 800);
}

void Game::initScene() {

    srand((int)time(NULL));

    for (int i = 0; i < 30; i++) {

        float randX = (float)(rand() % this->videoMode.width);
        float randY = (float)(rand() % this->videoMode.height);
        float randSpeed = 1;//3.0;
        float randDir = (float)(rand() % 360);

        entities.push_back(new Glider(randX, randY, randSpeed, randDir));
    }
}

void Game::initWindow() {
    this->window = new sf::RenderWindow(this->videoMode, "Not the Boids", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(144);
}

const bool Game::running() {
	return this->window->isOpen();
}

sf::RenderWindow* Game::getWindow() {
    return this->window;
}

std::vector<Entity*>& Game::getEntities() {
    return this->entities;
}