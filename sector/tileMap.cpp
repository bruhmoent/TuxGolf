//  LevelEditor
//  Copyright (C) 2024 bruhmoent
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

#include "tileMap.hpp"

TileMap::TileMap(TileData & _tile_data, int width, int height, const sf::Vector2f & grid_size)
    : tile_data(_tile_data), m_width(width), m_height(height), m_grid_size(grid_size) {
}

void TileMap::addTile(int id, const sf::Vector2f& position) {
    m_tiles.push_back({ id, position });
    m_tileIDs.push_back(id);
    loadSprites();
}

void TileMap::setTint(sf::Color tintColour) {
    m_tint = tintColour;
}

void TileMap::loadSprites() {
    for (auto& tile : m_tiles) {
        tile.sprite = createSprite(tile.id, tile.position);
        tile.sprite.setPosition(tile.position);
        tile.sprite.setColor(m_tint);
    }
}

void TileMap::snapTileMapTiles() {
    for (auto& tile : m_tiles) {
        tile.position.x = std::round(tile.position.x / m_grid_size.x) * m_grid_size.x;
        tile.position.y = std::round(tile.position.y / m_grid_size.y) * m_grid_size.y;
    }
}

void TileMap::removeTile(const sf::Vector2f& position) {
    auto tileToRemove = std::remove_if(m_tiles.begin(), m_tiles.end(), [&](const TileInfo& tile) {
        return tile.position == position;
        });

    m_tiles.erase(tileToRemove, m_tiles.end());
}

void TileMap::draw(sf::RenderWindow& window) {
    for (const auto& tile : m_tiles) {
        window.draw(tile.sprite);
    }
}

bool TileMap::isPositionOccupied(const sf::Vector2f& position) const {
    for (const auto& tile : m_tiles) {
        sf::FloatRect tileBounds(tile.position.x, tile.position.y, m_grid_size.x, m_grid_size.y);

        if (tileBounds.contains(position)) {
            return true;
        }
    }

    return false;
}

void TileMap::assignTilePositions(const std::vector<uint32_t>& ids) {
    m_tiles.clear();

    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            int index = y * m_width + x;
            if (index < ids.size()) {
                int id = ids[index];
                sf::Vector2f position(x * m_grid_size.x, y * m_grid_size.y);
                addTile(id, position);
            }
        }
    }
}

sf::Vector2f TileMap::getPositionFromIndex(int index) const {
    int x = index % static_cast<int>(m_width);
    int y = index / static_cast<int>(m_width);
    return sf::Vector2f(x * m_grid_size.x, y * m_grid_size.y);
}

void TileMap::clearTiles() {
    m_tileIDs.clear();
    m_tiles.clear();
}

sf::Sprite TileMap::createSprite(int id, const sf::Vector2f& position) {
    const sf::Texture* texture = &tile_data.getTexture(id);

    if (!texture || texture->getSize().x == 0 || texture->getSize().y == 0) {
        std::cerr << "Error: Texture not found for tile ID " << id << std::endl;
        return sf::Sprite();
    }

    sf::Sprite sprite;
    sprite.setTexture(*texture);
    sprite.setPosition(position);
    sprite.setScale(m_grid_size.x / texture->getSize().x, m_grid_size.y / texture->getSize().y);
    sprite.setColor(m_tint);
    return sprite;
}