#include "SFML\Graphics.hpp"

class enemies{
public:
	enemies();
	bool getActive();
	void setActive(bool);
	float getSpeed();
	float getsize();
	void setDirection(float);
	float getDirection();
	void setPosition(sf::Vector2f);
	sf::Vector2f getPosition();
	float getPositionx();
	float getPositiony();
private:
	bool active;
	float speed;
	float size;
	float direction;
	sf::Vector2f position;
};