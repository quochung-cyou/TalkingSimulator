#pragma once
#include "GameStateBase.h"
#include "IncludeHeader.h"
#include "Quiz.h"

class GSQuiz : public GameStateBase {
public:
	GSQuiz(int type);
	virtual ~GSQuiz();

	void exit();
	void pause();
	void resume();

	void init();
	void update(float deltaTime);
	void render();
private:
	float m_currentTime = 0.f;
	sf::Sprite m_background;
	float dt;
	sf::Event sfEvent;

	sf::Font fontText;
	sf::Text question, ans1, ans2, ans3, ans4;
	Quiz* currentQuiz;

	int cong_tutin = 0;
	int cong_code = 0;
	int cong_daicuong = 0;

	int correctAns = 0;

	int count = 1;

	int type = 0;

	std::map<std::string, sf::Sound> m_sounds;
	std::map<std::string, sf::SoundBuffer> m_soundBuffer;

	bool doneload = false;
};