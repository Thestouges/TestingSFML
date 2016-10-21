#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <stdlib.h>
#include <string>
#include <math.h>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "enemies.h"

class Game{
	public:
		Game();
		void run();
		void timer();
		void keyboardEvent();
		void mouseEvent();
		void createCharacter();
		void drawCharacter();
		void characterToMouse();
		void enemySpawn();
		void enemySpawner(int);
		void updateEnemies();
		void drawEnemy(int);
		bool collisioncheck(int);
	private:
		float movespeed;
		float characterx;
		float charactery;
		int characterSize;
		int windowx; 
		int windowy;
		sf::RenderWindow window;
		sf::Font font;
		sf::Clock clock;
		sf::Keyboard keyboard;
		sf::Mouse mouse;
		std::string keyPressed;
		std::string mousePressed;
		sf::Sprite player;
		sf::Texture playerTexture;
		float enemySpeed;
		float enemySize;
		int enemyamount;
		enemies *enemy;
		int enemyCounter;
		bool foundInactive;
		sf::Sprite enemySprite;
		sf::Vector2f enemyPosition;
		sf::Texture enemyTexture;
};