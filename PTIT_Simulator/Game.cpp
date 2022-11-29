#include "IncludeHeader.h"
#include "Game.h"
#include "Animation.h"
using namespace sf;

//Khoi chay bien
void Game::initVariables()
{
	this->window = NULL;

	this->dt = 0.f;

	this->gridSize = 64.f;
}


void Game::initWindow()
{

	this->window = new sf::RenderWindow(sf::VideoMode(sizeX, sizeY), "PTIT Simulator");
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(true);
}



Game::Game()
{
	this->initVariables();
	this->initWindow();
	WConnect->setWindow(this->window);
	GSM->changeState(StateTypes::INTRO);


	

}

Game::~Game()
{
	delete this->window;
}


void Game::updateDt()
{
	//Update delta time
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{

	while (this->window->pollEvent(this->sfEvent))
	{
		Event e = this->sfEvent;
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
	//	else if (e.type == sf::Event::KeyPressed)
	//	{
	//		AnimationHandler* animation = this->player->getAnimation();
	//		Movement* movement = this->player->getMovement();
	//		//std::cout << "key press " << this->player->getPosition().x << " " << this->player->getPosition().y << "\n";
	//		if (e.key.code == sf::Keyboard::Left)
	//			velocity.x = -200;
	//		else if (e.key.code == sf::Keyboard::Right)
	//			velocity.x = 200;
	//		else if (e.key.code == sf::Keyboard::Up)
	//			velocity.y = -200;
	//		else if (e.key.code == sf::Keyboard::Down)
	//			velocity.y = 200;
	//			
	//	}
	//	else if (e.type == sf::Event::KeyReleased)
	//	{
	//		if (e.key.code == sf::Keyboard::Left || e.key.code == sf::Keyboard::Right)
	//			velocity.x = 0;
	//		else if (e.key.code == sf::Keyboard::Up || e.key.code == sf::Keyboard::Down)
	//			velocity.y = 0;
	//	}


	//		auto deltaTime = this->dt;
	//		this->player->updateAnimation(dt);
	//		this->player->move(velocity.x, velocity.y, dt);
	//		
	//		
	//	
	//}

	
}

void Game::update()
{
	
	if (GSM->needToChangeState()) GSM->performSateChange();
	GSM->currentState()->update(this->dt);
	this->updateSFMLEvents();
}

void Game::render()
{
	this->window->clear();


	GSM->currentState()->render();



	this->window->display();

	
}

void Game::run()
{

	while (this->window->isOpen())
	{

		//Update delta time
		this->updateDt();

		//Update cac vat the
		this->update();

		//Render
		this->render();
	}
}

