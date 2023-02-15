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

	/*
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
	*/
}

void Glider::update(Game* game) {

	float visRange = 100;
	float protRange = 30;

	int margin = 50; // invis border
	float turnfactor = 0.2;
	float minSpeed = 2;
	float maxSpeed = 3;
	float avoidFactor = 0.05;

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
	/*
	for (Entity& e : game->getEntities()) {
		dx = this->x - e.getX();
		dy = this->y - e.getY();

		// if within visual range
		if (abs(dx) < visRange && abs(dy) < visRange) {
			distSquared = dx * dx + dy * dy;

			// if inside protected range
			if (distSquared < protRangeSquared) {
				closeDx += dx;
				closeDy += dy;
			}
			else if (distSquared < visRangeSquared) {
				xAvg += e.getX();
				yAvg += e.getY();
				vxAvg += e.getVX();
				vyAvg += e.getVY();

				neighbors++;
			}

		}

	}
	
	this->velocity.x += closeDx * avoidFactor;
	this->velocity.y += closeDy * avoidFactor;
	*/
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

	/*

	// edge of screen
	if (this->x < 0) {
		this->x = (float)game->getWindow()->getSize().x;
	}
	else if (this->x >= (float)game->getWindow()->getSize().x) {
		this->x = 0;
	}
	else if (this->y < 0) {
		this->y = (float)game->getWindow()->getSize().y;
	}
	else if (this->y >= (float)game->getWindow()->getSize().y) {
		this->y = 0;
	}

	*/

	this->x += this->velocity.x;
	this->y += this->velocity.y;

	/*
	for (Entity* e : game->getEntities()) {
		float dist = e->distance(*this);

		if (dist < 100 && dist != 0) {
			if (e->angle(*this) < 90) {
				
				this->direction += (-1 * e->angle(*this) + 90) / 90;
			}

		}
	}
	*/
}