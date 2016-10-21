#include <SFML\Graphics.hpp>

class gravity{
public:
	gravity();
	void simulate();
private:
	sf::Vector2f velocity;
};