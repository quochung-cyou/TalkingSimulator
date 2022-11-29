#pragma once
#include "SFML/Graphics.hpp"
#include "Singleton.h"
#include "Map.h"


#define MConnect MapConnector::GetInstance()

class MapConnector : public Singleton<MapConnector> {
public:
	MapConnector();
	void switchBack();
	Map* m_school;
	Map* m_home;
	Map* m_currentMap;


	int dayCount = 0; //dem ngay thu bao nhieu ?
	int tutin = 5;
	int daicuong = 5;
	int code = 5;


	
	int energyPlayer = 2;
	bool dayTalked[35] = {};


	int lastX = 200, lastY = 250;
	std::string lastMap = "school";
	std::string currentMap = "school";
	
};