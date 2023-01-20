// Entity.h
// Ethan Kerr

#pragma once

#include <SFML/Graphics.hpp>

class Game;

class Entity {
public:
	Entity();
	Entity(float x, float y);
	Entity(float x, float y, float speed, float direction);
	~Entity();

	virtual void draw(Game* game);
	virtual void update(Game* game);

	float getDirection();
	float getX();
	float getY();

	float distance(Entity& entity);
	sf::Vector2f toward(Entity& entity);
	float angle(Entity& entity);

protected:

	float x;
	float y;

	float speed;
	float direction;

private:

	void initVariables();

};

