#include "GSIntro.h"

GSIntro::GSIntro() {
	m_currentTime = 0;
}

GSIntro::~GSIntro() {
	RMInstance->removeTexture("intro");
}

void GSIntro::exit() {
}

void GSIntro::pause() {
}

void GSIntro::resume() {
}

void GSIntro::init() {
	m_logo.setTexture(*RMInstance->getTexture("intro"));
	m_logoColor = m_logo.getColor();
	WConnect->getWindow()->setMouseCursorVisible(false);
}

void GSIntro::update(float deltaTime) {
	m_currentTime += deltaTime;
	int opacity = 0;
	if (m_currentTime <= 1.f) {
		opacity = std::min(255, (int)round(255 * m_currentTime));
	}
	else if (m_currentTime <= 2.f) {
		opacity = 255;
	}
	else if (m_currentTime <= 3.f) {
		opacity = std::max(0, (int)round(255 * (3.f - m_currentTime)));
	}
	else {
		GSM->changeState(StateTypes::MENU);
		WConnect->getWindow()->setMouseCursorVisible(true);
		WConnect->getWindow()->setMouseCursorGrabbed(true);
		return;
	}
	m_logoColor.a = opacity;
	m_logo.setColor(m_logoColor);
}

void GSIntro::render() {
	WConnect->getWindow()->draw(m_logo);
}