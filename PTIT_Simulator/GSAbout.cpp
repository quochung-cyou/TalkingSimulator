#pragma once
#include "GSAbout.h"
#define TRANSITION_DURATION 0.5f

GSAbout::GSAbout() {
}

GSAbout::~GSAbout() {
}

void GSAbout::exit() {
}

void GSAbout::pause() {
}

void GSAbout::resume() {
}

void GSAbout::init() {
	std::cout << "init about state";

	//transition
	m_blackScreen = new sf::RectangleShape(sf::Vector2f(1024, 728));
	m_blackScreen->setFillColor(sf::Color::Black);
	isPerformTransition = true;
	m_currentTime = 0;


	//background
	m_background.setTexture(*RMInstance->getTexture("bgintro"));
	sf::Color bgColor = m_background.getColor();
	m_background.setColor(bgColor);



	//exit button
	GameButton* backBtn = new GameButton("btnExit", sf::Vector2f(305.f, 180.f));
	backBtn->init();
	backBtn->setPosition(sf::Vector2f(740.f, 600.f));
	backBtn->setOnClick([]() {GSM->changeState(MENU); });
	m_btnList.push_back(backBtn);

	//lmao
}

void GSAbout::update(float deltaTime) {
	//transition
	if (isPerformTransition == true) {
		m_currentTime += deltaTime;
		if (m_currentTime < TRANSITION_DURATION * 2) {
			sf::Color color = sf::Color::Black;
			color.a = 255 * (1 - (m_currentTime / (TRANSITION_DURATION * 2)));
			m_blackScreen->setFillColor(color);
		}
		else {
			isPerformTransition = false;
			m_blackScreen->setFillColor(sf::Color::Transparent);
			m_currentTime = 0;
			delete m_blackScreen;
		}
	}
	//menu update
	for (auto& btn : m_btnList) {
		btn->update(deltaTime);
	}
}

void GSAbout::render() {
	//logo
	WConnect->getWindow()->draw(m_background);
	//WConnect->getWindow()->draw(m_logo);
	//button
	for (auto& btn : m_btnList) {
		btn->render();
	}
	//transition
	if (isPerformTransition) WConnect->getWindow()->draw(*m_blackScreen);
}