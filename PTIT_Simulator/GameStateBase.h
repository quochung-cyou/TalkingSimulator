#pragma once
#include "ResourceManager.h"
#include "WindowConnector.h"
#include "GameStateMachine.h"



class GameStateBase {
public:
	GameStateBase() {};
	virtual ~GameStateBase() {};

	virtual void exit() = 0;
	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;

	static GameStateBase* createState(StateTypes state);
};