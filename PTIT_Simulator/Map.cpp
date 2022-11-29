#include "Map.h"
#define mapSizeX 64
#define mapSizeY 45
#define tileSize 16
using namespace std;

Map::Map(int amount, std::string resourceID) {
    this->layerAmount = amount;
    this->m_tileMap = vector<vector<vector<Tile*>>>(amount + 5, vector<vector<Tile*>>(mapSizeY + 5, vector<Tile*>(mapSizeX + 5)));
    this->m_mapID = vector<vector<vector<int>>>(amount + 5, vector<vector<int>>(mapSizeY + 5, vector<int>(mapSizeX + 5)));
    this->resourceID = resourceID;
}

void Map::Init() {

    for (int layer = 0; layer < layerAmount; layer++) {
        for (int i = 0; i < mapSizeY; i++) {
            for (int j = 0; j < mapSizeX; j++) {
                if (m_mapID[layer][i][j] != 0) {
                    m_tileMap[layer][i][j] = new Tile(m_mapID[layer][i][j], sf::Vector2i(i, j));
                    m_tileMap[layer][i][j]->Init(resourceID);
                    if (m_mapID[layer][i][j] == -1) {
                        m_tileMap[layer][i][j]->SetTileType(SOLID);
                        this->listSolid.push_back(m_tileMap[layer][i][j]);
                    }
                    else {
                        m_tileMap[layer][i][j]->SetTileType(NONE);
                    }
                }
            }
        }
    }
}

void Map::Update(float deltaTime, Player* entity) {

    //WORLD BOUNDS
    if (entity->getPosition().x < 0.f)
    {
        entity->setPosition(0.f, entity->getPosition().y);
        entity->stopVelocityX();
    }
    else if (entity->getPosition().x + entity->getGlobalBounds().width > this->GetMapSize().x)
    {
        entity->setPosition(this->GetMapSize().x - entity->getGlobalBounds().width, entity->getPosition().y);
        entity->stopVelocityX();
    }
    if (entity->getPosition().y < 0.f)
    {
        entity->setPosition(entity->getPosition().x, 0.f);
        entity->stopVelocityY();
    }
    else if (entity->getPosition().y + entity->getGlobalBounds().height > this->GetMapSize().y)
    {
        entity->setPosition(entity->getPosition().x, this->GetMapSize().y - entity->getGlobalBounds().height);
        entity->stopVelocityY();
    }

    //TILES

    for (int i = 0; i < listSolid.size(); i++) {
        sf::FloatRect playerBounds = entity->getGlobalBounds();
        sf::FloatRect wallBounds = this->listSolid[i]->GetHitBox()->getGlobalBounds();
        sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(deltaTime);
        if (this->listSolid[i]->GetHitBox()->intersects(nextPositionBounds)) {
            //Bottom collision
            if (playerBounds.top < wallBounds.top
                && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
                && playerBounds.left < wallBounds.left + wallBounds.width
                && playerBounds.left + playerBounds.width > wallBounds.left
                )
            {
                entity->stopVelocityY();
                entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
            }

            //Top collision
            else if (playerBounds.top > wallBounds.top
                && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
                && playerBounds.left < wallBounds.left + wallBounds.width
                && playerBounds.left + playerBounds.width > wallBounds.left
                )
            {
                entity->stopVelocityY();
                entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
            }

            //Right collision
            if (playerBounds.left < wallBounds.left
                && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
                && playerBounds.top < wallBounds.top + wallBounds.height
                && playerBounds.top + playerBounds.height > wallBounds.top
                )
            {
                entity->stopVelocityX();
                entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
            }

            //Left collision
            else if (playerBounds.left > wallBounds.left
                && playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
                && playerBounds.top < wallBounds.top + wallBounds.height
                && playerBounds.top + playerBounds.height > wallBounds.top
                )
            {
                entity->stopVelocityX();
                entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
            }




        }

    }
}





void Map::Render(sf::RenderWindow* window) {
    for (int layer = 0; layer < layerAmount; layer++) {
        for (int i = 0; i < mapSizeY; ++i) {
            for (int j = 0; j < mapSizeX; ++j) {
                if (m_mapID[layer][i][j] != 0) {
                    m_tileMap[layer][i][j]->Render(window);
                }
            }
        }
    }
}

sf::Vector2f Map::GetMapSize() {
    return sf::Vector2f(tileSize * mapSizeX, tileSize * mapSizeY);
}
