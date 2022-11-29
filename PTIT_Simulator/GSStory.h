#pragma once
#include "IncludeHeader.h"
#include "GameStateBase.h"

class GSStory : public GameStateBase {
public:
	GSStory();
	virtual ~GSStory();

	void exit();
	void pause();
	void resume();

	void init();
	void update(float deltaTime);
	void render();
private:
	sf::Sprite storyBg;
	float m_currentTime = 0;
	sf::RectangleShape* m_blackScreen;
	bool state1 = false, state2 = false, state3 = false;
	sf::Sound *sound;
	sf::SoundBuffer *soundBuffer;
};