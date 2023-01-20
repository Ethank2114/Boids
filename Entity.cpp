// Entity.cpp
// Ethan Kerr

#include "Game.h"
#include "Entity.h"


const double PI = 3.14159265358979;

Entity::Entity() {
	this->initVariables();
}

Entity::Entity(float x, float y) {
	this->x = x;
	this->y = y;
	this->speed = 0;
	this->direction = 0;
}

Entity::Entity(float x, float y, float speed, float direction) {
	this->x = x;
	this->y = y;
	this->speed = speed;
	this->direction = direction;
}

Entity::~Entity() {
	
}

void Entity::initVariables() {
	this->x = 0;
	this->y = 0;
	this->speed = 0;
	this->direction = 0;
}

float Entity::getDirection() {
	return this->direction;
}

float Entity::getX() {
	return x;
}

float Entity::getY() {
	return y;
}

float Entity::distance(Entity& entity) {
	return sqrt(pow(entity.x - this->x, 2) + pow(entity.y - this->y, 2));
}

sf::Vector2f Entity::toward(Entity& entity) {
	float mag = this->distance(entity);
	return sf::Vector2f((this->x - entity.x), (this->y - entity.y)) / mag;
}

float Entity::angle(Entity& entity) {
	sf::Vector2f p1 = sf::Vector2f(cos(this->direction * (PI / 180)), sin(this->direction * (PI / 180)));
	sf::Vector2f p2 = sf::Vector2f(entity.getX() - this->x, entity.getY() - this->y);

	float top = p1.x * p2.x + p1.y * p2.y;
	float bottom = sqrt(pow(p2.x, 2) + pow(p2.y, 2));

	float out = (bottom != 0) ? top / bottom  : 0;

	return std::acos(out) * (180 / PI);
}

void Entity::draw(Game* game) {

	sf::RectangleShape rect(sf::Vector2f(16, 16));
	rect.setFillColor(sf::Color(135, 135, 135, 255));
	rect.setPosition(this->x, this->y);

	game->getWindow()->draw(rect);
}

void Entity::update(Game* game) {
	this->x += this->speed * (float)cos(this->direction * (PI/180));
	this->y -= this->speed * (float)sin(this->direction * (PI/180));

	if (this -> x < 0) {
		this->x = (float)game->getWindow()->getSize().x;
	} else if (this->x >= game->getWindow()->getSize().x) {
		this->x = 0;
	} else if (this->y < 0) {
		this->y = (float)game->getWindow()->getSize().y;
	} else if (this->y >= game->getWindow()->getSize().y) {
		this->y = 0;
	}
}