#pragma once
#include "Singleton.h"
#include <list>
#include "IncludeHeader.h"
#define GSM GameStateMachine::GetInstance()


class GameStateBase;

enum StateTypes {
	INVALID = 0,
	INTRO,
	MENU,
	ABOUT,
	PLAY,
	STORY,
	QUIZDAICUONG,
	QUIZCODE,
	END
};

//egjnhoefgjikoeoifef





class GameStateMachine : public Singleton<GameStateMachine> {
public:
	GameStateMachine();
	~GameStateMachine();

	void changeState(GameStateBase* state);
	void changeState(StateTypes state);
	void pushState(StateTypes state);
	void popState();

	void performSateChange();

	GameStateBase* currentState() const;
	GameStateBase* nextState() const;
	bool needToChangeState();
	bool hasState();

private:
	std::list<GameStateBase*> m_StateStack;
	GameStateBase* m_ActiveState;
	GameStateBase* m_NextState;

	sf::Sound* sound;
	sf::SoundBuffer* soundBuffer;
};