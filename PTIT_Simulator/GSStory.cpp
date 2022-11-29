#include "GSStory.h"
#include "IncludeHeader.h"
GSStory::GSStory() {
	m_currentTime = 0;
}

GSStory::~GSStory() {
	
}

void GSStory::exit() {
}

void GSStory::pause() {
}

void GSStory::resume() {
}




void GSStory::init() {
	storyBg.setTexture(*RMInstance->getTexture("story1"));
	WConnect->getWindow()->setMouseCursorVisible(false);
	sf::SoundBuffer buffer;

	this->soundBuffer = new sf::SoundBuffer;
	this->sound = new sf::Sound;
	if (!this->soundBuffer->loadFromFile("../Resource/Sound/single.wav"))
	{
		return;
	}
	this->sound->setBuffer(* this->soundBuffer);
	this->sound->play();
	this->sound->setLoop(true);

}

void GSStory::update(float deltaTime) {
	
	m_currentTime += deltaTime;
	if (m_currentTime <= 3.f && !state1) {
		state1 = true;
		storyBg.setTexture(*RMInstance->getTexture("story1"));
	}
	else if (m_currentTime > 3.f && m_currentTime <= 6.f && !state2) {
		storyBg.setTexture(*RMInstance->getTexture("story2"));
		state2 = true;
	}
	else if (m_currentTime > 6.f && m_currentTime <= 9.f && !state3) {
		state3 = true;
		storyBg.setTexture(*RMInstance->getTexture("story3"));
	}
	else if (m_currentTime > 9.f) {
		GSM->changeState(StateTypes::PLAY);
		WConnect->getWindow()->setMouseCursorVisible(false);
		WConnect->getWindow()->setMouseCursorGrabbed(false);
		this->sound->stop();
		return;
	}
}

void GSStory::render() {
	WConnect->getWindow()->draw(storyBg);
}