#pragma once
#include "GameStateBase.h"
#include "GameButton.h"
#include "IncludeHeader.h"

class GSMenu : public GameStateBase {
public:
	GSMenu();
	virtual ~GSMenu();

	void exit();
	void pause();
	void resume();

	void init();
	void update(float deltaTime);
	void render();
private:
	std::list<GameButton*> m_btnList;

	float m_currentTime = 0.f;
	sf::Sprite m_background;
	sf::Sprite m_logo;
	sf::RectangleShape* m_blackScreen;
	bool isPerformTransition = false;

	sf::Sound* sound;
	sf::SoundBuffer* soundBuffer;
};