#include "IncludeHeader.h"
#include "Player.h"
#include "Animation.h"

//Initializer functions
void Player::initVariables()
{
	this->textureBubble.loadFromFile("../Resource/Chat/3dot.png");
	this->speechBubble.setTexture(this->textureBubble);

	this->font = new sf::Font;
	this->font->loadFromFile("../Resource/Font/font.ttf");

	this->npcName.setFont(* this->font);
	this->npcName.setCharacterSize(20);
	this->npcName.setFillColor(sf::Color::White);
	this->npcName.setString(this->getName());
	
}

void Player::setFace(sf::Sprite face) {
	this->face = face;
}

void Player::initComponents()
{

}

Player * Player::getChattingWith() {
	return this->chattingWith;
}

void Player::setChattingWith(Player* target) {
	this->chattingWith = target;
}

std::string Player::getName() {
	return this->name;
}

sf::Sprite Player::getFace() {
	return this->face;
}

void Player::initAnimations()
{
	//int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height
	this->animation->addAnimation("IDLE", 3.f, 0, 10, 8, 10, 64, 64);
	this->animation->addAnimation("WALK_UP", 3.f, 0, 8, 8, 8, 64, 64);
	this->animation->addAnimation("WALK_LEFT", 3.f, 0, 9, 8, 9, 64, 64);
	this->animation->addAnimation("WALK_RIGHT", 3.f, 0, 11, 8, 11, 64, 64);
	this->animation->addAnimation("WALK_DOWN", 3.f, 0, 10, 8, 10, 64, 64);
}


//Constructors / Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet, std::string name)
{

	this->name = name;
	this->initVariables();
	this->createAnimation(texture_sheet);
	this->createHitbox(this->sprite, 14.f, 20.f, 38.f, 40.f);
	this->createMovement(100.f, 1400.f, 500.f);

	this->setPosition(x, y);
	
	this->initAnimations();
}

Player::~Player()
{
}

void Player::emote(std::string s, const float &dt, float duration) {
	isEmoting = true;
	emotesDuration = duration;
	emotesCurtime = 0;
	emotecount = 0;
	if (s == "question") {
		this->textures["emote1"].loadFromFile("../Resource/Emoji/tile003.png");
		this->textures["emote2"].loadFromFile("../Resource/Emoji/tile004.png");
		this->textures["emote3"].loadFromFile("../Resource/Emoji/tile005.png");
	}
	if (s == "think") {
		this->textures["emote1"].loadFromFile("../Resource/Emoji/tile003.png");
		this->textures["emote2"].loadFromFile("../Resource/Emoji/tile004.png");
		this->textures["emote3"].loadFromFile("../Resource/Emoji/tile005.png");
	}
	if (s == "scare") {
		this->textures["emote1"].loadFromFile("../Resource/Emoji/tile096.png");
		this->textures["emote2"].loadFromFile("../Resource/Emoji/tile097.png");
		this->textures["emote3"].loadFromFile("../Resource/Emoji/tile098.png");
	}
	if (s == "fun") {
		this->textures["emote1"].loadFromFile("../Resource/Emoji/tile015.png");
		this->textures["emote2"].loadFromFile("../Resource/Emoji/tile016.png");
		this->textures["emote3"].loadFromFile("../Resource/Emoji/tile017.png");
	}
	if (s == "love") {
		this->textures["emote1"].loadFromFile("../Resource/Emoji/tile024.png");
		this->textures["emote2"].loadFromFile("../Resource/Emoji/tile025.png");
		this->textures["emote3"].loadFromFile("../Resource/Emoji/tile026.png");
	}
	if (s == "exit") {
		this->textures["emote1"].loadFromFile("../Resource/Emoji/tile459.png");
		this->textures["emote2"].loadFromFile("../Resource/Emoji/tile460.png");
		this->textures["emote3"].loadFromFile("../Resource/Emoji/tile461.png");
	}
	if (s == "action") {
		this->textures["emote1"].loadFromFile("../Resource/Emoji/tile537.png");
		this->textures["emote2"].loadFromFile("../Resource/Emoji/tile538.png");
		this->textures["emote3"].loadFromFile("../Resource/Emoji/tile539.png");
	}
	if (s == "clock") {
		this->textures["emote1"].loadFromFile("../Resource/Emoji/tile216.png");
		this->textures["emote2"].loadFromFile("../Resource/Emoji/tile217.png");
		this->textures["emote3"].loadFromFile("../Resource/Emoji/tile218.png");
	}
	if (s == "learn") {
		this->textures["emote1"].loadFromFile("../Resource/Emoji/tile204.png");
		this->textures["emote2"].loadFromFile("../Resource/Emoji/tile205.png");
		this->textures["emote3"].loadFromFile("../Resource/Emoji/tile206.png");
	}
	if (s == "tired") {
		this->textures["emote1"].loadFromFile("../Resource/Emoji/tile174.png");
		this->textures["emote2"].loadFromFile("../Resource/Emoji/tile175.png");
		this->textures["emote3"].loadFromFile("../Resource/Emoji/tile176.png");
	}
	if (s == "wtf") {
		this->textures["emote1"].loadFromFile("../Resource/Emoji/tile075.png");
		this->textures["emote2"].loadFromFile("../Resource/Emoji/tile076.png");
		this->textures["emote3"].loadFromFile("../Resource/Emoji/tile077.png");
	}
	emotes.clear();
	sf::Sprite emote1, emote2, emote3;
	emote1.setTexture(this->textures["emote1"]);
	emote2.setTexture(this->textures["emote2"]);
	emote3.setTexture(this->textures["emote3"]);
	emotes.push_back(emote1); emotes.push_back(emote2); emotes.push_back(emote3);
	
}

void Player::updateAnimation(const float& dt)
{
	if (this->movement->getState(IDLE))
	{
		this->animation->play("IDLE", dt);
	}
	else if (this->movement->getState(MOVING_LEFT))
	{
		this->animation->play("WALK_LEFT", dt, this->movement->getVelocity().x, this->movement->getMaxVelocity());
	}
	else if (this->movement->getState(MOVING_RIGHT))
	{
		this->animation->play("WALK_RIGHT", dt, this->movement->getVelocity().x, this->movement->getMaxVelocity());
	}
	else if (this->movement->getState(MOVING_UP))
	{
		this->animation->play("WALK_UP", dt, this->movement->getVelocity().y, this->movement->getMaxVelocity());
	}
	else if (this->movement->getState(MOVING_DOWN))
	{
		this->animation->play("WALK_DOWN", dt, this->movement->getVelocity().y, this->movement->getMaxVelocity());
	}
}

void Player::update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view)
{
	this->movement->update(dt);

	this->updateAnimation(dt);

	this->hitbox->update();
}


void Player::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movement) {
		this->movement->update(dt);
		this->movement->move(dir_x, dir_y, dt);
		this->updateAnimation(dt);
		this->hitbox->update();

	}
	//Sets velocity
}

void Player::showSpeechBubble(sf::RenderTarget& target) {
	if (!isEmoting) {
		this->speechBubble.setPosition(this->getPosition().x - 5, this->getPosition().y - 30);
		target.draw(this->speechBubble);
	}

}

void Player::render(sf::RenderTarget& target, const bool show_hitbox, float deltaTime)
{
	//std::cout << "Render player\n";



	if (show_hitbox) {
		target.draw(this->sprite);
		this->npcName.setPosition(this->getPosition().x + 10, this->getPosition().y - 30);
		target.draw(this->npcName);
	}

	
	

	

	if (isEmoting) {
		if (emotesCurtime < emotesDuration) {
			emotesCurtime += deltaTime;
		}
		else {
			isEmoting = false;
		}
		emotecount++;
		if (emotecount >= 30) emotecount = 0;
		
		if (emotecount <= 10) {
			emotes[0].setPosition(this->getPosition().x, this->getPosition().y - 30);
			target.draw(emotes[0]);
		}
		else if (emotecount <= 20) {
			emotes[1].setPosition(this->getPosition().x, this->getPosition().y - 30);
			target.draw(emotes[1]);
		}
		else {
			emotes[2].setPosition(this->getPosition().x, this->getPosition().y - 30);
			target.draw(emotes[2]);
		}
	}

	
}
