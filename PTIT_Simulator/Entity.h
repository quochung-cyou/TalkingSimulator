#pragma once

#include "IncludeHeader.h"
#include "Movement.h"
#include "Animation.h"
#include "Hitbox.h"

class Hitbox;

class Entity
{
private:
	void initVariables();
protected:
	sf::Sprite sprite;
	Hitbox* hitbox;
	AnimationHandler *animation;
	Movement* movement;

public:
	Entity();
	virtual ~Entity();

	//Component functions
	void setTexture(sf::Texture& texture);
	void createHitbox(sf::Sprite& sprite,
		float offset_x, float offset_y,
		float width, float height);
	void createMovement(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimation(sf::Texture& texture_sheet);

	//Accessors
	virtual Movement* getMovement();
	virtual AnimationHandler* getAnimation();
	virtual Hitbox* getHitbox();

	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::Vector2f& getSpritePosition() const;
	virtual const sf::Vector2f getCenter() const;
	virtual const sf::Vector2f getSpriteCenter() const;
	virtual const sf::Vector2i getGridPosition(const int gridSizeI) const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::FloatRect getNextPositionBounds(const float& dt) const;

	//Modifiers
	virtual void setPosition(const float x, const float y);

	//Functions
	virtual void move(const float x, const float y, const float& dt);
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();

	//Calculations
	virtual const float getDistance(const Entity& entity) const;
	virtual const float getSpriteDistance(const Entity& entity) const;

	virtual void update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view) = 0;
	virtual void render(sf::RenderTarget& target, const bool show_hitbox, float deltaTime) = 0;
};



