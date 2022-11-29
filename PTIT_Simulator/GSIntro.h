#pragma once
#include "GameStateBase.h"
#include "IncludeHeader.h"

class GSIntro : public GameStateBase {
public:
	GSIntro();
	virtual ~GSIntro();

	void exit();
	void pause();
	void resume();

	void init();
	void update(float deltaTime);
	void render();
private:
	sf::Sprite m_logo;
	sf::Color m_logoColor;
	float m_currentTime;
};