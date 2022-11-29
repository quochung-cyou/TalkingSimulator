#pragma once
#include "Hitbox.h"
#include "ResourceManager.h"


enum TileType {
	NONE,
	SOLID,
};

class Tile {
public:
	static sf::Vector2f m_scale;
	Tile(int id, sf::Vector2i position);
	void Init(std::string resourceID);
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	void SetTileType(TileType tileType);
	TileType GetTileType();
	Hitbox* GetHitBox();
	void setSprite(sf::Texture);
	//Collider* GetCollider();
private:
	int tileId;
	TileType m_tileType;
	sf::Sprite* m_sprite;
	sf::Vector2i m_position;
	Hitbox* m_hitBox;
	//Collider* m_collider;
};