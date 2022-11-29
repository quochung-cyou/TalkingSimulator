#include "IncludeHeader.h"
#include "Entity.h"

void Entity::initVariables()
{
	this->hitbox = NULL;
	this->movement = NULL;
	this->animation = NULL;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->hitbox;
	delete this->movement;
	delete this->animation;
}

//Component functions
void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::createAnimation(sf::Texture& texture_sheet) {
	this->animation = new AnimationHandler(this->sprite, texture_sheet);
}

void Entity::createHitbox(sf::Sprite& sprite,
	float offset_x, float offset_y,
	float width, float height)
{
	this->hitbox = new Hitbox(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovement(const float maxVelocity, const float acceleration, const float deceleration)
{
	this->movement = new Movement(this->sprite, maxVelocity, acceleration, deceleration);
}


Movement* Entity::getMovement()
{
	return this->movement;
}

Hitbox* Entity::getHitbox()
{
	return this->hitbox;
}

AnimationHandler* Entity::getAnimation()
{
	return this->animation;
}

const sf::Vector2f& Entity::getPosition() const
{
	if (this->hitbox)
		return this->hitbox->getPosition();

	return this->sprite.getPosition();
}

const sf::Vector2f& Entity::getSpritePosition() const
{
	return this->sprite.getPosition();
}

const sf::Vector2f Entity::getCenter() const
{
	if (this->hitbox)
		return
		this->hitbox->getPosition() +
		sf::Vector2f
		(
			this->hitbox->getGlobalBounds().width / 2.f,
			this->hitbox->getGlobalBounds().height / 2.f
		);

	return
		this->sprite.getPosition() +
		sf::Vector2f
		(
			this->sprite.getGlobalBounds().width / 2.f,
			this->sprite.getGlobalBounds().height / 2.f
		);
}

const sf::Vector2f Entity::getSpriteCenter() const
{
	return this->sprite.getPosition() +
		sf::Vector2f
		(
			this->sprite.getGlobalBounds().width / 2.f,
			this->sprite.getGlobalBounds().height / 2.f
		);;
}

const sf::Vector2i Entity::getGridPosition(const int gridSizeI) const
{
	if (this->hitbox)
		return sf::Vector2i(
			static_cast<int>(this->hitbox->getPosition().x) / gridSizeI,
			static_cast<int>(this->hitbox->getPosition().y) / gridSizeI
		);

	return sf::Vector2i(
		static_cast<int>(this->sprite.getPosition().x) / gridSizeI,
		static_cast<int>(this->sprite.getPosition().y) / gridSizeI
	);
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->hitbox)
		return this->hitbox->getGlobalBounds();

	return this->sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPositionBounds(const float& dt) const
{
	if (this->hitbox && this->movement)
		return this->hitbox->getNextPosition(this->movement->getVelocity() * dt);

	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

//Functions



void Entity::setPosition(const float x, const float y)
{
	if (this->hitbox)
		this->hitbox->setPosition(x, y);
	else
		this->sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	std::cout << "move\n";
	if (this->movement) {
		this->movement->move(dir_x, dir_y, dt);

	}
		 //Sets velocity
}

void Entity::stopVelocity()
{
	if (this->movement)
		this->movement->stopVelocity();

}

void Entity::stopVelocityX()
{
	if (this->movement)
		this->movement->stopVelocityX();
}

void Entity::stopVelocityY()
{
	if (this->movement)
		this->movement->stopVelocityY();
}

const float Entity::getDistance(const Entity& entity) const
{
	return sqrt(pow(this->getCenter().x - entity.getCenter().x, 2) + pow(this->getCenter().y - entity.getCenter().y, 2));
}

const float Entity::getSpriteDistance(const Entity& entity) const
{
	return sqrt(pow(this->getSpriteCenter().x - entity.getSpriteCenter().x, 2) + pow(this->getSpriteCenter().y - entity.getSpriteCenter().y, 2));
}