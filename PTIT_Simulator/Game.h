#ifndef GAME_H
#define GAME_H
#include "IncludeHeader.h"
#include "ResourceManager.h"
#include "GameStateMachine.h"
#include "GameStateBase.h"


class Game
{
private:
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	
	std::map<std::string, int> supportedKeys;

	float gridSize;

	//Initialization
	void initVariables();
	void initWindow();

public:
	//Constructors/Destructors
	Game();
	virtual ~Game();

	//Functions

	//Regular
	void endApplication();

	//Update
	void updateDt();
	void updateSFMLEvents();
	void update();

	//Render
	void render();

	//Core
	void run();
};

#endif