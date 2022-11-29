#include "GSEnd.h"
#include "MapConnector.h"

GSEnd::GSEnd() {

}

GSEnd::~GSEnd() {


}

void GSEnd::exit() {
	this->endMusic.stop();
}

void GSEnd::pause() {
}

void GSEnd::resume() {
}

void GSEnd::init() {
	if (MConnect->tutin <= 0) {
		m_backGround.setTexture(*RMInstance->getTexture("ed/1"));
	}
	else if (MConnect->code <= 0) {
		m_backGround.setTexture(*RMInstance->getTexture("ed/2"));
	}
	else if (MConnect->daicuong <= 0) {
		m_backGround.setTexture(*RMInstance->getTexture("ed/3"));
	}
	else if (MConnect->code >= 30 && MConnect->code < 90) {
		m_backGround.setTexture(*RMInstance->getTexture("ed/4"));
	}
	else if (MConnect->code >= 90 && MConnect->code < 150) {
		m_backGround.setTexture(*RMInstance->getTexture("ed/5"));
	}
	else if (MConnect->code >= 150) {
		m_backGround.setTexture(*RMInstance->getTexture("ed/6"));
	}
	else if (MConnect->daicuong >= 30 && MConnect->daicuong < 90) {
		m_backGround.setTexture(*RMInstance->getTexture("ed/7"));
	}
	else if (MConnect->daicuong >= 90 && MConnect->daicuong < 150) {
		m_backGround.setTexture(*RMInstance->getTexture("ed/8"));
	}
	else if (MConnect->daicuong >= 150) {
		m_backGround.setTexture(*RMInstance->getTexture("ed/9"));
	}
	else {
		m_backGround.setTexture(*RMInstance->getTexture("ed/1"));
	}
	//init walk sound
	if (!this->endMusic.openFromFile("../Resource/Sound/sadend.wav")) {
		std::cout << "Loi am thanh\n";
		return;
	}

	//Sound play
	this->endMusic.play();
	this->endMusic.setLoop(true);
	
}

void GSEnd::update(float deltaTime) {
	m_currentTime += deltaTime;
	if (m_currentTime> 10.f) {
		GSM->changeState(StateTypes::MENU);
		WConnect->getWindow()->setMouseCursorVisible(true);
		WConnect->getWindow()->setMouseCursorGrabbed(true);
		return;
	}
}

void GSEnd::render() {
	WConnect->getWindow()->draw(m_backGround);
}