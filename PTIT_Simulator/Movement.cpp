#pragma once
#include "IncludeHeader.h"
#include "Movement.h"

Movement::Movement(sf::Sprite& sprite,
	float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite),
	maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{

}

Movement::~Movement()
{
}

const float& Movement::getMaxVelocity() const
{
	return this->maxVelocity;
}

const sf::Vector2f& Movement::getVelocity() const
{
	return this->velocity;
}

const bool Movement::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:

		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
			return true;

		break;

	case MOVING:

		if (this->velocity.x != 0.f || this->velocity.y != 0.f)
			return true;

		break;

	case MOVING_LEFT:

		if (this->velocity.x < 0.f)
			return true;

		break;

	case MOVING_RIGHT:

		if (this->velocity.x > 0.f)
			return true;

		break;

	case MOVING_UP:

		if (this->velocity.y < 0.f)
			return true;

		break;

	case MOVING_DOWN:

		if (this->velocity.y > 0.f)
			return true;

		break;
	}

	return false;
}

void Movement::stopVelocity()
{
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}

void Movement::stopVelocityX()
{
	this->velocity.x = 0.f;
}

void Movement::stopVelocityY()
{

	this->velocity.y = 0.f;
}

void Movement::move(const float dir_x, const float dir_y, const float& dt)
{

	this->velocity.x += this->acceleration * dir_x * dt;
	this->velocity.y += this->acceleration * dir_y * dt;
	this->update(dt);
}

void Movement::update(const float& dt)
{

	if (this->velocity.x > 0.f) 
	{
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;
		this->velocity.x -= deceleration * dt;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}
	else if (this->velocity.x < 0.f) 
	{
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;
		this->velocity.x += deceleration * dt;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}

	if (this->velocity.y > 0.f) 
	{
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;
		this->velocity.y -= deceleration * dt;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
	}
	else if (this->velocity.y < 0.f) 
	{
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;
		this->velocity.y += deceleration * dt;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}
	this->sprite.move(this->velocity * dt); 
}
