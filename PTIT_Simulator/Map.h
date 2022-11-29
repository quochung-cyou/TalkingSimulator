#pragma once
#include "Tile.h"
#include <list>
using namespace std;

class Map {
public:
	Map(int layerAmount, std::string resourceID);
	void Init();
	void Update(float deltaTime, Player * player);
	void Render(sf::RenderWindow* window);
	sf::Vector2f GetMapSize();
	int layerAmount;
	vector<vector<vector<int>>> m_mapID;
	vector<vector<vector<Tile*>>> m_tileMap;
	vector<Tile*> listSolid;
	std::string resourceID;
};