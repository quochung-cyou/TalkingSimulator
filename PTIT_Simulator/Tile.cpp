#include "Tile.h"


const sf::Vector2f globalScale(1.f, 1.f);
sf::Vector2f Tile::m_scale = 1.f * globalScale;
#define tileSize 16
Tile::Tile(int id, sf::Vector2i position) {
	m_sprite = new sf::Sprite();
	tileId = id - 1;
	m_position = position;
}

void Tile::setSprite(sf::Texture texture) {
	m_sprite->setTexture(texture);
}

void Tile::Init(std::string resourceID) {
	m_hitBox = new Hitbox(*this->m_sprite, 0, 0, tileSize, tileSize);
	m_hitBox->setPosition(sf::Vector2f(m_position.y * tileSize * m_scale.y + tileSize * m_scale.y / 2, m_position.x * tileSize * m_scale.x + tileSize * m_scale.x / 2));
	if (RMInstance->hasTexture(resourceID + "/" + std::to_string(this->tileId))) {
		//std::cout << "lmao can't load " << std::to_string(this->tileId) << "\n";
		
	}
	if (this->tileId != -2) m_sprite->setTexture(*RMInstance->getTexture(resourceID + "/" + std::to_string(this->tileId)));
	//else m_sprite->setTexture(*RMInstance->getTexture("tile/0"));
	 
	
	
	
	m_sprite->setPosition(sf::Vector2f(m_position.y * tileSize, m_position.x * tileSize));
	//m_sprite->setScale(m_scale);

}

void Tile::Update(float deltaTime) {
}

void Tile::Render(sf::RenderWindow* window) {
	window->draw(*m_sprite);
	//this->m_hitBox->render(* window);
}

void Tile::SetTileType(TileType tileType) {
	m_tileType = tileType;
}

TileType Tile::GetTileType() {
	return m_tileType;
}

Hitbox* Tile::GetHitBox() {
	return m_hitBox;
}