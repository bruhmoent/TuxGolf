//  LevelEditor
//  Copyright (C) 2023 bruhmoent
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "tile.hpp"
#include "tiles.hpp"
#include "tileData.hpp"
#include "tileMaps.hpp"
#include "tileMap.hpp"

void Tiles::addTileToTileMap(const TileData& tileData, int id, const sf::Vector2f& mousePosition, const sf::Vector2f& gridSize, const sf::Vector2u& levelSize, TileMaps& tileMaps, int tileMapID)
{
    const std::string& texturePath = tileData.getTexturePath(id);
    if (texturePath.empty()) {
        std::cout << "Invalid tile ID: " << id << std::endl;
        return;
    }

    auto textureIt = m_textureDictionary.find(texturePath);
    std::shared_ptr<sf::Texture> tileTexture;

    if (textureIt != m_textureDictionary.end()) {
        tileTexture = textureIt->second;
    }
    else {
        tileTexture = std::make_shared<sf::Texture>();
        if (!tileTexture->loadFromFile(texturePath)) {
            std::cout << "Failed to load texture: " << texturePath << std::endl;
            return;
        }
        m_textureDictionary[texturePath] = tileTexture;
    }

    sf::RectangleShape tileShape(sf::Vector2f(tileTexture->getSize().x, tileTexture->getSize().y));
    sf::Vector2f mousePos(mousePosition.x, mousePosition.y);

    Tile* tile = new Tile(sf::Sprite(*tileTexture), tileShape, mousePos, id);

    sf::Vector2u textureSize = tileTexture->getSize();
    float scaleX = gridSize.x / textureSize.x;
    float scaleY = gridSize.y / textureSize.y;
    tile->m_sprite.setScale(scaleX, scaleY);

    float snappedX = std::floor(tile->m_position.x / gridSize.x) * gridSize.x;
    float snappedY = std::floor(tile->m_position.y / gridSize.y) * gridSize.y;
    tile->m_position = sf::Vector2f(snappedX, snappedY);

    sf::Vector2f maxGrids = sf::Vector2f(levelSize.x / gridSize.x, levelSize.y / gridSize.y);
    if (tile->m_position.x < 0 || tile->m_position.y < 0 || tile->m_position.x >= maxGrids.x * gridSize.x || tile->m_position.y >= maxGrids.y * gridSize.y) {
        delete tile;
        return;
    }

    tile->m_onTileMapID = tileMapID;
    tileMaps.m_tileMaps[tile->m_onTileMapID]->addTile(tile, *this);

    m_tiles.push_back(tile);
}

void 
Tiles::removeTile(const sf::Vector2f& position)
{
	m_tiles.erase(
		std::remove_if(m_tiles.begin(), m_tiles.end(),
			[position](const auto& tile) { return tile->m_position == position; }),
		m_tiles.end()
	);
}

void
Tiles::snapAllTilesToGrid(const sf::Vector2f& gridSize) {
	for (Tile*& tile : m_tiles) {
		float snappedX = std::floor(tile->m_position.x / gridSize.x) * gridSize.x;
		float snappedY = std::floor(tile->m_position.y / gridSize.y) * gridSize.y;

		tile->m_position = sf::Vector2f(snappedX, snappedY);
		tile->m_sprite.setPosition(tile->m_position);
	}
}

bool
Tiles::isPositionOccupied(const sf::Vector2f& position) const
{
	for (const Tile* tile : m_tiles) {
		if (tile->m_position == position) {
			return true;
		}
	}
	return false;
}