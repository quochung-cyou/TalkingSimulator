#pragma once
#include "GameStateBase.h"
#include "IncludeHeader.h"

class GSEnd : public GameStateBase {
public:
	GSEnd();
	virtual ~GSEnd();

	void exit();
	void pause();
	void resume();

	void init();
	void update(float deltaTime);
	void render();
private:
	sf::Sprite m_backGround;
	float m_currentTime = 0.f;
	sf::Music endMusic;
};