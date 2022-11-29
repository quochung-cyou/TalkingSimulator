#include "WindowConnector.h"

WindowConnector::WindowConnector() {
    m_window = nullptr;
}

void WindowConnector::setWindow(sf::RenderWindow* window) {
    m_window = window;
}

sf::RenderWindow* WindowConnector::getWindow() {
    return m_window;
}