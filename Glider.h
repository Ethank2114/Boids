// Glider.h
// Ethan Kerr

#pragma once

#include <SFML/Graphics.hpp>

class Game;
class Entity;

class Glider: public Entity {
public:

	Glider(float x, float y, float speed, float direction);

	void draw(Game* game);
	void update(Game* game);
private:

	sf::Color color;
};

