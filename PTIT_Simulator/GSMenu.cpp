#pragma once
#include "GSMenu.h"
#define TRANSITION_DURATION 0.5f

GSMenu::GSMenu() {
}

GSMenu::~GSMenu() {

}

void GSMenu::exit() {
	this->sound->stop();
}

void GSMenu::pause() {
}

void GSMenu::resume() {
}

void GSMenu::init() {

	sf::SoundBuffer soundBuffer;
	this->soundBuffer = new sf::SoundBuffer;
	this->sound = new sf::Sound;
	if (!this->soundBuffer->loadFromFile("../Resource/Sound/bgmgame.wav"))
	{
		return;
	}
	this->sound->setBuffer(*this->soundBuffer);
	this->sound->play();
	this->sound->setLoop(true);


	std::cout << "init menu state";

	//transition
	m_blackScreen = new sf::RectangleShape(sf::Vector2f(1024, 728));
	m_blackScreen->setFillColor(sf::Color::Black);
	isPerformTransition = true;
	m_currentTime = 0;


	//background
	m_background.setTexture(*RMInstance->getTexture("bg"));
	sf::Color bgColor = m_background.getColor();
	m_background.setColor(bgColor);



	//play button
	GameButton* playBtn = new GameButton("btnPlay", sf::Vector2f(305.f, 180.f));
	playBtn->init();
	playBtn->setPosition(sf::Vector2f(140.f, 600.f));
	playBtn->setOnClick([]() {
		

		GSM->changeState(STORY); 

	});
	m_btnList.push_back(playBtn);

	//about button
	GameButton* aboutBtn = new GameButton("btnAbout", sf::Vector2f(305.f, 180.f));
	aboutBtn->init();
	aboutBtn->setPosition(sf::Vector2f(490.f, 600.f));
	aboutBtn->setOnClick([]() {
		std::cout << "click about button\n";
		GSM->changeState(ABOUT); 
	});
	m_btnList.push_back(aboutBtn);

	//exit button
	GameButton* exitBtn = new GameButton("btnExit", sf::Vector2f(305.f, 180.f));
	exitBtn->init();
	exitBtn->setPosition(sf::Vector2f(890.f, 600.f));
	exitBtn->setOnClick([]() {
		std::cout << "click exit button\n";
		WConnect->getWindow()->close(); 
	});
	m_btnList.push_back(exitBtn);

	//lmao
}

void GSMenu::update(float deltaTime) {
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
	//menu update, cập nhật nút
	for (auto& btn : m_btnList) {
		btn->update(deltaTime);
	}
}

void GSMenu::render() {
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