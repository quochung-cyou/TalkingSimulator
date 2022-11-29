#include "GameButton.h"

GameButton::GameButton() {
    m_btnClickFunc = nullptr;
    m_isHandling = false;
    m_btnName = "";
}

GameButton::GameButton(std::string name, sf::Vector2f size) : GameButton() {
    m_btnName = name;
    this->setSize(size);
    this->setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
}

GameButton::~GameButton() {
}

void GameButton::init() {
    this->setTexture(RMInstance->getTexture("gui/" + m_btnName + "_idle"));
}

void GameButton::update(float deltaTime) {
    if (this->getGlobalBounds().contains(
        (sf::Vector2f)sf::Mouse::getPosition(*WConnect->getWindow())
    )) {
        this->setTexture(RMInstance->getTexture("gui/" + m_btnName + "_handle"));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            m_btnClickFunc();
            m_isHandling = true;
        }
    }
    else {
        this->setTexture(RMInstance->getTexture("gui/" + m_btnName + "_idle"));
    }
}

void GameButton::render() {
    WConnect->getWindow()->draw(*this);
}

bool GameButton::isHandle() {
    return m_isHandling;
}

void GameButton::setOnClick(void(*Func)()) {
    m_btnClickFunc = Func;
}