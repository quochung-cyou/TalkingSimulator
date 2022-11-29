#pragma once
#include "GameStateBase.h"
#include "GameButton.h"

class GSAbout : public GameStateBase {
public:
	GSAbout();
	virtual ~GSAbout();

	void exit();
	void pause();
	void resume();

	void init();
	void update(float deltaTime);
	void render();
private:
	std::list<GameButton*> m_btnList;

	float m_currentTime;
	sf::Sprite m_background;
	sf::Sprite m_logo;
	sf::RectangleShape* m_blackScreen;
	bool isPerformTransition;
};