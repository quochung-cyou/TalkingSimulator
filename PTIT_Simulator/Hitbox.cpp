#pragma once
#include "IncludeHeader.h"
#include "Hitbox.h"

Hitbox::Hitbox(sf::Sprite& sprite,
	float offset_x, float offset_y,
	float width, float height)
	: sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
	this->nextPosition.left = 0.f;
	this->nextPosition.top = 0.f;
	this->nextPosition.width = width;
	this->nextPosition.height = height;

	this->hitbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
	this->hitbox.setSize(sf::Vector2f(width, height));
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(-1.f);
	this->hitbox.setOutlineColor(sf::Color::Green);

}

Hitbox::~Hitbox()
{
}



//Accessors
const sf::Vector2f& Hitbox::getPosition() const
{
	return this->hitbox.getPosition();
}

const sf::FloatRect Hitbox::getGlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}

const sf::FloatRect& Hitbox::getNextPosition(const sf::Vector2f& velocity)
{
	this->nextPosition.left = this->hitbox.getPosition().x + velocity.x;
	this->nextPosition.top = this->hitbox.getPosition().y + velocity.y;

	return this->nextPosition;
}

//Modifiers
void Hitbox::setPosition(const sf::Vector2f& position)
{
	this->hitbox.setPosition(position);
	this->sprite.setPosition(position.x - this->offsetX, position.y - this->offsetY);
}

void Hitbox::setPosition(const float x, const float y)
{
	this->hitbox.setPosition(x, y);
	this->sprite.setPosition(x - this->offsetX, y - this->offsetY);
}

//Functions
bool Hitbox::intersects(const sf::FloatRect& frect)
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}

void Hitbox::update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
}

void Hitbox::render(sf::RenderTarget &target)
{
	target.draw(this->hitbox);
}
