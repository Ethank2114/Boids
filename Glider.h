// Glider.h
// Ethan Kerr

#pragma once

#include <SFML/Graphics.hpp>

class Game;
class Entity;

class Glider: public Entity {
public:

	Glider(float x, float y, sf::Vector2f& velocity);

	void draw(Game* game);
	void update(Game* game);

private:

	sf::Color color;
};

