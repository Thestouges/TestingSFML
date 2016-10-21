#include "enemies.h"

enemies::enemies(){
	speed = .2;
	size = 10;
	active = false;
}

bool enemies::getActive(){
	return active;
}

void enemies::setActive(bool setValue){
	active = setValue;
}

float enemies::getSpeed(){
	return speed;
}

float enemies::getsize(){
	return size;
}

void enemies::setDirection(float setValue){
	direction = setValue;
}

float enemies::getDirection(){
	return direction;
}

void enemies::setPosition(sf::Vector2f pos){
	position = pos;
}

sf::Vector2f enemies::getPosition(){
	return position;
}

float enemies::getPositionx(){
	return position.x;
}
float enemies::getPositiony(){
	return position.y;
}