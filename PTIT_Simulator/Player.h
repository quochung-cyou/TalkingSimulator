#pragma once
#include "Entity.h"
#include "IncludeHeader.h"
#include "Animation.h"
class Entity;

class Player :
	public Entity
{
private:
	void initVariables();
	void initComponents();
	void initAnimations();


	Player * chattingWith;
	sf::Texture textureBubble;
	sf::Sprite speechBubble;
	sf::Sprite face;
	std::string name;
	sf::Text npcName;
	sf::Font * font;
	std::vector<sf::Sprite> emotes;
	float emotesCurtime = 0, emotesDuration = 0;
	int emotecount = 0;
	std::map<std::string, sf::Texture> textures;
	bool isEmoting = false;




public:
	Player(float x, float y, sf::Texture& texture_sheet, std::string name);



	virtual ~Player();
	void emote(std::string s, const float& dt, float duration);


	void setFace(sf::Sprite face);
	sf::Sprite getFace();



	void updateAnimation(const float& dt);
	void update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view);
	void render(sf::RenderTarget& target, const bool show_hitbox, float deltaTime);
	void showSpeechBubble(sf::RenderTarget& target);
	void move(const float x, const float y, const float& dt);
	Player* getChattingWith();
	void setChattingWith(Player * target);
	std::string getName();
};

