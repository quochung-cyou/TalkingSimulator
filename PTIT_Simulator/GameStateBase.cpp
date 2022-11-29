#include "GameStateBase.h"
#include "GSIntro.h"
#include "GSMenu.h"
#include "GSPlay.h"
#include "GSAbout.h"
#include "GSStory.h"
#include "GSQuiz.h"
#include "GSEnd.h"

GameStateBase* GameStateBase::createState(StateTypes state) {
	GameStateBase* gameState = nullptr;
	switch (state) {
	case INVALID:
		break;
	case INTRO:
		gameState = new GSIntro();
		break;
	case MENU:
		gameState = new GSMenu();
		break;
	case ABOUT:
		gameState = new GSAbout();
		break;
	case PLAY:
		gameState = new GSPlay();
		break;
	case STORY:
		gameState = new GSStory();
		break;
	case QUIZDAICUONG:
		gameState = new GSQuiz(1);
		break;
	case QUIZCODE:
		gameState = new GSQuiz(2);
		break;
	case END:
		gameState = new GSEnd();
		break;
	default:
		break;
	}
	return gameState;
}