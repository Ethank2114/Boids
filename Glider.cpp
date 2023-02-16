// Glider.cpp
// Ethan Kerr

#include "Entity.h"
#include "Glider.h"
#include "Game.h"

#include <iostream>

const double PI = 3.14159265358979;

Glider::Glider(float x, float y, sf::Vector2f& velocity):
	Entity(x, y, velocity) {

	this->color = sf::Color(0, rand() % 255, 100 + rand() % 155, 255);
}

void Glider::draw(Game* game) {

	sf::VertexArray trig(sf::Triangles, 3);

	trig[0].position = sf::Vector2f(this->x, this->y);

	float length = 25;

	//sf::Vector2f heading = sf::Vector2f(length * (float)cos(this->direction * (PI / 180)),
		//length * (float)sin(this->direction * (PI / 180)));

	float vx = this->velocity.x;
	float vy = this->velocity.y;
	float mag = sqrt(vx * vx + vy * vy);

	sf::Vector2f heading = length * (this->velocity / mag);

	sf::Vector2f normal = sf::Vector2f(-1 * heading.y / 3,heading.x / 3);

	trig[1].position = sf::Vector2f(this->x - heading.x + normal.x, this->y - heading.y + normal.y);
	trig[2].position = sf::Vector2f(this->x - heading.x - normal.x, this->y - heading.y - normal.y);

	trig[0].color = this->color;
	trig[1].color = this->color;
	trig[2].color = this->color;

	game->getWindow()->draw(trig);

}

void Glider::update(Game* game) {

	float visRange = 150;
	float protRange = 25;

	int margin = 50; // invis border
	float turnfactor = 0.2f;
	float minSpeed = 3;
	float maxSpeed = 4;
	float avoidFactor = 0.008f;
	float centerFactor = 0.00025f;
	float matchFactor = 0.025f;

	float dx = 0;
	float dy = 0;
	float distSquared = 0;
	float visRangeSquared = visRange * visRange;
	float protRangeSquared = protRange * protRange;
	float closeDx = 0; // combined distance of close others
	float closeDy = 0; // combined distance of close others
	float xAvg = 0;
	float yAvg = 0;
	float vxAvg = 0;
	float vyAvg = 0;
	int neighbors = 0;
	
	for (Entity* e : game->getEntities()) {
		dx = this->x - e->getX();
		dy = this->y - e->getY();

		// if within visual range
		if (abs(dx) < visRange && abs(dy) < visRange) {
			distSquared = dx * dx + dy * dy;

			// if inside protected range
			if (distSquared < protRangeSquared) {
				closeDx += dx;
				closeDy += dy;
			}
			else if (distSquared < visRangeSquared) {
				xAvg += e->getX();
				yAvg += e->getY();
				vxAvg += e->getVX();
				vyAvg += e->getVY();

				neighbors++;
			}
		}
	}

	if (neighbors > 0) {
		xAvg /= neighbors;
		yAvg /= neighbors;
		vxAvg /= neighbors;
		vyAvg /= neighbors;

		this->velocity.x += (xAvg - this->x) * centerFactor + (vxAvg - this->velocity.x) * matchFactor;
		this->velocity.y += (yAvg - this->y) * centerFactor + (vyAvg - this->velocity.y) * matchFactor;

	}
	
	// Avoidance of others
	this->velocity.x += closeDx * avoidFactor;
	this->velocity.y += closeDy * avoidFactor;
	
	// edge avoidance
	if (this->x < margin) {
		this->velocity.x += turnfactor;
	}
	if (this->x > (float)game->getWindow()->getSize().x - margin) {
		this->velocity.x -= turnfactor;
	}
	if (this->y < margin) {
		this->velocity.y += turnfactor;
	}
	if (this->y > (float)game->getWindow()->getSize().y - margin) {
		this->velocity.y -= turnfactor;
	}


	// Enforce min and max speed
	float vx = this->velocity.x;
	float vy = this->velocity.y;

	float speed = sqrt(vx * vx + vy * vy);

	if (speed < minSpeed) {
		this->velocity.x *= minSpeed / speed;
		this->velocity.y *= minSpeed / speed;
	}
	if (speed > maxSpeed) {
		this->velocity.x *= maxSpeed / speed;
		this->velocity.y *= maxSpeed / speed;
	}


	// Update position
	this->x += this->velocity.x;
	this->y += this->velocity.y;
}