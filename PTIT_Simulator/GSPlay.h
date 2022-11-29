#pragma once
#include "GameStateBase.h"
#include "IncludeHeader.h"
#include "DialogSystem.h"
#include "Map.h"

class GSPlay : public GameStateBase {
public:
	GSPlay();
	virtual ~GSPlay();
	sf::Event sfEvent;
	void exit();
	void pause();
	void resume();
	void init();
	void update(float deltaTime);
	void render();
	void startLoadingScreen();

	void addQueueDialog(sf::Sprite face, wchar_t text[], std::string npcName, std::string emotes, Player* player);

private:
	float m_currentTime;
	sf::RectangleShape* m_blackScreen;
	bool isPerformTransition;
	bool isPlayText;
	
	sf::Sprite m_background, energy1, energy2;
	float dt;
	sf::Font dialogFont;


	sf::Text displayDay, displayTuTin, displayCode, displayDaiCuong;


	Player* player;
	std::vector<Player*> npcList;
	std::vector<Player*> objectList;

	bool isLoadingScreen = false;
	float isLoadingScreen_time = 0;
	float ppmWalk = 0.f;



	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::Sprite> sprites;
	std::map<std::string, sf::Sound> m_sounds;
	std::map<std::string, sf::SoundBuffer> m_soundBuffer;

	


	std::queue<DialogSystem*> queueDialog;



	sf::Sound* walksound;
	
	sf::Music bgmsound;


	sf::SoundBuffer* soundBuffer;
	sf::SoundBuffer* bgmSoundBuffer;


	Map* curMap;
};