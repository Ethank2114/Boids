// Glider.cpp
// Ethan Kerr

#include "Entity.h"
#include "Glider.h"
#include "Game.h"

#include <iostream>

const double PI = 3.14159265358979;

Glider::Glider(float x, float y, float speed, float direction):
	Entity(x, y, speed, direction) {
	this->color = sf::Color(0, rand() % 255, 100 + rand() % 155, 255);
}

void Glider::draw(Game* game) {

	sf::VertexArray trig(sf::Triangles, 3);

	trig[0].position = sf::Vector2f(this->x, this->y);

	float length = 25;

	sf::Vector2f heading = sf::Vector2f(length * (float)cos(this->direction * (PI / 180)),
		length * sin(this->direction * (PI / 180)));

	sf::Vector2f normal = sf::Vector2f(-1 * heading.y / 3,heading.x / 3);

	trig[1].position = sf::Vector2f(this->x - heading.x + normal.x, this->y - heading.y + normal.y);
	trig[2].position = sf::Vector2f(this->x - heading.x - normal.x, this->y - heading.y - normal.y);

	trig[0].color = this->color;
	trig[1].color = this->color;
	trig[2].color = this->color;

	game->getWindow()->draw(trig);

	Entity* closest = nullptr;
	float closestDist = FLT_MAX;

	for (Entity* e : game->getEntities()) {
		float dist = e->distance(*this);
		
		if (dist < closestDist && dist != 0) {
			if (e->angle(*this) < 90) {
				//std::cout << e->angle(*this) << std::endl;
				closest = e;
				closestDist = e->distance(*this);
			}
			
		}
	}

	//std::cout << this->angle(*closest) << std::endl;

	// nullptr guard
	if (closest == nullptr) {
		return;
	}

	sf::VertexArray line(sf::LineStrip, 2);
	line[0].position = sf::Vector2f(this->x, this->y);
	line[1].position = sf::Vector2f(closest->getX(), closest->getY());


	line[0].color = this->color;
	line[1].color = this->color;

	game->getWindow()->draw(line);

}

void Glider::update(Game* game) {
	this->x += this->speed * (float)cos(this->direction * (PI / 180));
	this->y += this->speed * (float)sin(this->direction * (PI / 180));

	if (this->x < 0) {
		this->x = game->getWindow()->getSize().x;
	}
	else if (this->x >= game->getWindow()->getSize().x) {
		this->x = 0;
	}
	else if (this->y < 0) {
		this->y = game->getWindow()->getSize().y;
	}
	else if (this->y >= game->getWindow()->getSize().y) {
		this->y = 0;
	}

	
	for (Entity* e : game->getEntities()) {
		float dist = e->distance(*this);

		if (dist < 100 && dist != 0) {
			if (e->angle(*this) < 90) {
				
				this->direction += (-1 * e->angle(*this) + 90) / 90;
			}

		}
	}
}