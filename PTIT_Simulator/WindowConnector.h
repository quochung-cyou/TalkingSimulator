#pragma once
#include "SFML/Graphics.hpp"
#include "Singleton.h"

#define WConnect WindowConnector::GetInstance()

class WindowConnector : public Singleton<WindowConnector> {
public:
	WindowConnector();
	void setWindow(sf::RenderWindow* window);
	sf::RenderWindow* getWindow();
private:
	sf::RenderWindow* m_window;
};