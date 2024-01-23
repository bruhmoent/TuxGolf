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

#include "tiles.hpp"
#include "tileMap.hpp"
#include "tile.hpp"

void TileMap::snapTileMapTiles() {
    for (Tile*& tile : m_tileMapTiles) {
        float snappedX = std::floor(tile->m_position.x / m_gridSize.x) * m_gridSize.x;
        float snappedY = std::floor(tile->m_position.y / m_gridSize.y) * m_gridSize.y;

        tile->m_position = sf::Vector2f(snappedX, snappedY);
        tile->m_sprite.setPosition(tile->m_position);
    }
}

void 
TileMap::setTileSize(const sf::Vector2f& tileSize) {
    for (Tile*& tile : m_tileMapTiles) {
        tile->setSize(tileSize);
    }
}

void 
TileMap::addTile(Tile* tile, Tiles& tiles) {
    for (Tile* existingTile : m_helperMapTiles) {
        if (existingTile->m_position == tile->m_position) {
            return;
        }
    }

    m_helperMapTiles.push_back(new Tile(*tile));
    m_tileMapTiles.push_back(new Tile(*tile));
}

void 
TileMap::tintTiles(sf::Color tintColour) {
    for (Tile* tile : m_tileMapTiles) {
        tile->tint(tintColour);
    }
}

void 
TileMap::setOpacity(int value) {
    opacity = value;
}

void 
TileMap::draw(sf::RenderWindow& window) {
    for (Tile* tile : m_tileMapTiles) {
        sf::Color tileColor = tile->m_sprite.getColor();
        tile->m_sprite.setColor(sf::Color(tileColor.r, tileColor.g, tileColor.b, opacity));
        tile->m_sprite.setPosition(tile->m_position);
        window.draw(tile->m_sprite);
    }
}

void 
TileMap::displayTiles(sf::RenderWindow& window) {
    draw(window);
}

void 
TileMap::setGrid(const sf::Vector2f & gridSize) {
    m_gridSize = gridSize;
}