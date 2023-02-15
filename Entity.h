// Entity.h
// Ethan Kerr

#pragma once

#include <SFML/Graphics.hpp>

class Game;

class Entity {
public:
	Entity();
	Entity(float x, float y);
	Entity(float x, float y, sf::Vector2f& velocity);
	//Entity(float x, float y, float speed, float direction);
	~Entity();

	virtual void draw(Game* game);
	virtual void update(Game* game);

	float getDirection();
	float getX();
	float getY();
	float getVX();
	float getVY();

	sf::Vector2f& getVelocity();

	float distance(Entity& entity);
	//sf::Vector2f toward(Entity& entity);
	//float angle(Entity& entity);

protected:

	float x;
	float y;

	//float speed;
	//float direction;

	sf::Vector2f velocity;

private:

	void initVariables();

};

