#pragma once
#include "ResourceManager.h"
#include "WindowConnector.h"

class GameButton : public sf::RectangleShape {
public:
	GameButton();
	GameButton(std::string name, sf::Vector2f size);
	~GameButton();

	void init();
	void update(float deltaTime);
	void render();

	bool isHandle();

	void setOnClick(void(*Func)());

protected:
	void (*m_btnClickFunc)();
	bool m_isHandling;
	std::string m_btnName;
};