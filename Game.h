// Game.h
// Ethan Kerr

#pragma once

#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>

class Entity;

class Game {
public:
	Game();
	~Game();

	void update();
	void render();

	const bool running();
	sf::RenderWindow* getWindow();
	std::vector<Entity*>& getEntities();

private:

	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	std::vector<Entity*> entities = std::vector<Entity*>();

	void initVariables();
	void initScene();
	void initWindow();

	void pollEvents();
};

