#include "Game.h"

Game::Game(){
	run();
}

void Game::run(){
	windowx = 800;
	windowy = 600;
	movespeed = .4;
	enemyamount = 100;
	enemy = new enemies[enemyamount];
	enemySpeed = .5;
	enemySize = 10;
	enemyCounter = 0;
	foundInactive = false;
	characterx = windowx/2;
	charactery = windowy/2;
	characterSize = 10;
	createCharacter();
	window.create(sf::VideoMode(windowx, windowy), "SFML works!");

	if (!font.loadFromFile("times.ttf")){
		// error...
	}

	if (!enemyTexture.loadFromFile("sphereSprite.jpg")){
		// error...
	}

	enemySprite.setTexture(enemyTexture);
	enemySprite.setColor(sf::Color::Red);

	while (window.isOpen())
    {
		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		window.clear(sf::Color::Black);
		timer();
		keyboardEvent();
		mouseEvent();
		drawCharacter();
		enemySpawn();
		updateEnemies();
		characterToMouse();
		window.display();
    }
}

void Game::timer(){
	sf::Text timertext;
	sf::Time elapsed = clock.getElapsedTime();
	timertext.setString(std::to_string(elapsed.asSeconds()));
	sf::sleep(sf::milliseconds(1));

	timertext.setFont(font);
	timertext.setCharacterSize(12);
	timertext.setFillColor(sf::Color::White);

	window.draw(timertext);
}

void Game::keyboardEvent(){
	sf::Text keyboardtext;
	keyboardtext.setFont(font);
	keyboardtext.setCharacterSize(12);
	keyboardtext.setFillColor(sf::Color::Red);

	if(keyboard.isKeyPressed(sf::Keyboard::Right) && characterx+2*characterSize <= windowx){
		if(keyboard.isKeyPressed(sf::Keyboard::Up) && charactery >= 0){
			keyPressed = "RightUp";
			characterx+=movespeed;
			charactery-=movespeed;
		}
		else if(keyboard.isKeyPressed(sf::Keyboard::Down) && charactery+2*characterSize <= windowy){
			keyPressed = "RightDown";
			characterx+=movespeed;
			charactery+=movespeed;
		}
		else{
			keyPressed = "Right";
			characterx+=movespeed;
		}
	}
	else if(keyboard.isKeyPressed(sf::Keyboard::Left) && characterx >= 0){
		if(keyboard.isKeyPressed(sf::Keyboard::Up) && charactery >= 0){
			keyPressed = "LeftUp";
			characterx-=movespeed;
			charactery-=movespeed;
		}
		else if(keyboard.isKeyPressed(sf::Keyboard::Down) && charactery+2*characterSize <= windowy){
			keyPressed = "LeftDown";
			characterx-=movespeed;
			charactery+=movespeed;
		}
		else{
			keyPressed = "Left";
			characterx-=movespeed;
		}
	}
	else if(keyboard.isKeyPressed(sf::Keyboard::Up) && charactery >= 0){
		keyPressed = "Up";
		charactery-=movespeed;
	}
	else if(keyboard.isKeyPressed(sf::Keyboard::Down) && charactery+2*characterSize <= windowy){
		keyPressed = "Down";
		charactery+=movespeed;
	}
	
	keyboardtext.setString(keyPressed);
	keyboardtext.setPosition(windowx/4,0);
	window.draw(keyboardtext);
}

void Game::mouseEvent(){
	sf::Text mousetext;
	mousetext.setFont(font);
	mousetext.setCharacterSize(12);
	mousetext.setFillColor(sf::Color::Blue);

	if(mouse.isButtonPressed(sf::Mouse::Left))
		mousePressed = "Left Button";
	else if(mouse.isButtonPressed(sf::Mouse::Right))
		mousePressed = "Right Button";
	else if(mouse.isButtonPressed(sf::Mouse::Middle))
		mousePressed = "Middle Button";

	mousetext.setString(mousePressed);
	mousetext.setPosition(windowx/2,0);
	window.draw(mousetext);
}

void Game::createCharacter(){
	if (!playerTexture.loadFromFile("playerSprite.png")){
		// error...
	}
	player.setTexture(playerTexture);
	player.setScale(characterSize*.01,characterSize*.01);
	player.setColor(sf::Color::Green);
}

void Game::drawCharacter(){
	sf::Text playertext;
	playertext.setFont(font);
	playertext.setCharacterSize(12);
	playertext.setFillColor(sf::Color::Green);
	playertext.setString("x:"+std::to_string(characterx)+" y:"+std::to_string(charactery));
	playertext.setPosition(0,windowy*.1);
	window.draw(playertext);

	player.setPosition(characterx,charactery);
	window.draw(player);
}

void Game::characterToMouse(){
	sf::Text angletext;
	angletext.setFont(font);
	angletext.setCharacterSize(12);
	angletext.setFillColor(sf::Color::Yellow);

	sf::Text mousetext;
	mousetext.setFont(font);
	mousetext.setCharacterSize(12);
	mousetext.setFillColor(sf::Color::Yellow);
	mousetext.setPosition(3*windowx/4,0);

	sf::RectangleShape line(sf::Vector2f(150,1));
	line.setPosition(characterx+characterSize,charactery+characterSize);
	sf::Vector2i mousePosition = mouse.getPosition(window);

	float angle = atan2(charactery+characterSize-mousePosition.y, characterx+characterSize-mousePosition.x);
	angle = angle*(180/M_PI);
	line.rotate(angle-180);

	mousetext.setString("x:"+std::to_string(mousePosition.x)+" y:"+std::to_string(mousePosition.y)+" angle:"+std::to_string(angle));

	window.draw(mousetext);
//	window.draw(line);
	
}

void Game::enemySpawn(){
	if(std::rand()%100+1 <= 33){
		for(int i = 0; i < enemyamount; i++){
			if(!enemy[i].getActive()){
				enemyCounter = i;
				foundInactive = true;
				break;
			}
		}
	}
	if(foundInactive){
		foundInactive = false;
		enemy[enemyCounter].setActive(true);
		enemySpawner(enemyCounter);
	}
}

void Game::enemySpawner(int value){
	int edgespawn = std::rand()%2;
	int xory = std::rand()%2;
	sf::Vector2f location;
	if(xory){
		if(edgespawn){ // Top Spawn
			location.x = std::rand()%windowx-enemy[value].getsize();
			location.y = 0;
			enemy[value].setDirection(1);
		}
		else{ // Bottom Spawn
			location.x = std::rand()%windowx-enemy[value].getsize();
			location.y = windowy-2*enemy[value].getsize();
			enemy[value].setDirection(2);
		}
	}
	else{
		if(edgespawn){ // Left Spawn
			location.x = 0;
			location.y = std::rand()%windowy-enemy[value].getsize();
			enemy[value].setDirection(3);
		}
		else{ // Right Spawn
			location.x = windowx-2*enemy[value].getsize();
			location.y = std::rand()%windowy-enemy[value].getsize();
			enemy[value].setDirection(4);
		}
	}
	enemy[value].setPosition(location);
}

void Game::updateEnemies(){
	for(int i = 0; i < enemyamount; i++){
		if(enemy[i].getActive()){
			drawEnemy(i);
			if(enemy[i].getDirection() == 1 && enemy[i].getPositiony() < windowy){ // Top
				enemyPosition.x = enemy[i].getPositionx();
				enemyPosition.y = enemy[i].getPositiony()+enemy[i].getSpeed();
			}
			else if(enemy[i].getDirection() == 2 && enemy[i].getPositiony() > 0){ // Bottom
				enemyPosition.x = enemy[i].getPositionx();
				enemyPosition.y = enemy[i].getPositiony()-enemy[i].getSpeed();
			}
			else if(enemy[i].getDirection() == 3 && enemy[i].getPositionx() < windowx){ // Left
				enemyPosition.x = enemy[i].getPositionx()+enemy[i].getSpeed();;
				enemyPosition.y = enemy[i].getPositiony();
			}
			else if(enemy[i].getDirection() == 4 && enemy[i].getPositionx() < 0){ // Right
				enemyPosition.x = enemy[i].getPositionx()-enemy[i].getSpeed();;
				enemyPosition.y = enemy[i].getPositiony();
			}
			else{
				enemy[i].setActive(false);
			}
			enemy[i].setPosition(enemyPosition);
			collisioncheck(i);
		}
	}
}

void Game::drawEnemy(int value){
	enemySprite.setScale(enemy[value].getsize()/200,enemy[value].getsize()/200);
	enemySprite.setPosition(enemy[value].getPosition());

	window.draw(enemySprite);
}

bool Game::collisioncheck(int value){
	sf::Vector2f playerPos = player.getPosition();
	if(player.getGlobalBounds().intersects(enemySprite.getGlobalBounds())){
		std::cout<<"Collided with enemy #"<<value<<std::endl;
		return true;
	}
	return false;
}