#include "ResourceManager.h"

ResourceManager::ResourceManager() {
	m_Path = "../Data/";
	m_TexturePath = m_Path + "Texture/";
	m_FontPath = m_Path + "Font/";
}

ResourceManager::~ResourceManager() {
	for (auto it : m_MapTexture) {
		if (it.second != nullptr) delete it.second;
	}
	m_MapTexture.clear();
}

void ResourceManager::addTexture(std::string name) {
	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile(m_TexturePath + name + ".png");
	if (m_MapTexture.count(name)) return;
	m_MapTexture.insert({ name, texture });
}

void ResourceManager::removeTexture(std::string name) {
	auto it = m_MapTexture.find(name);
	if (it == m_MapTexture.end()) return;
	if (it->second == nullptr) return;
	else delete it->second;
	m_MapTexture.erase(it);
}

sf::Texture* ResourceManager::getTexture(std::string name) {
	auto it = m_MapTexture.find(name);
	if (it == m_MapTexture.end()) {
		addTexture(name);
		return getTexture(name);
	}
	return it->second;
}

bool ResourceManager::hasTexture(std::string name) {
	return m_MapTexture.count(name);
}

void ResourceManager::addFont(std::string name) {
	sf::Font* font = new sf::Font;
	font->loadFromFile(m_FontPath + name + ".ttf");
	if (m_MapFont.count(name)) return;
	m_MapFont.insert({ name, font });
}

void ResourceManager::removeFont(std::string name) {
	auto it = m_MapFont.find(name);
	if (it == m_MapFont.end()) return;
	if (it->second == nullptr) return;
	else delete it->second;
	m_MapFont.erase(it);
}

sf::Font* ResourceManager::getFont(std::string name) {
	auto it = m_MapFont.find(name);
	if (it == m_MapFont.end()) {
		addFont(name);
		return getFont(name);
	}
	return it->second;
}

bool ResourceManager::hasFont(std::string name) {
	return m_MapFont.count(name);
}

void ResourceManager::setCursor(std::string name) {
	if (m_customCursor != nullptr) delete m_customCursor;
	m_customCursor = new sf::Image();
	m_customCursor->loadFromFile(m_TexturePath + name + ".png");
}

sf::Image* ResourceManager::getCursor() {
	return m_customCursor;
}