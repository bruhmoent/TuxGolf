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

#ifndef TILE_MAP_HPP
#define TILE_MAP_HPP

#include <SFML/Graphics.hpp>
#include "tileData.hpp"

class TileMap {
public:
    //FIXME: A clean up would be handy.
    TileMap(TileData& _tile_data, int width, int height, const sf::Vector2f& grid_size);

    void addTile(int id, const sf::Vector2f& position);
    void setTint(sf::Color tintColour);
    void loadSprites();
    void draw(sf::RenderWindow& window);
    void assignTilePositions(const std::vector<uint32_t>& ids);
    const std::vector<uint32_t>& getTileIDs() const {
        return m_tileIDs;
    }

    sf::Vector2f getPositionFromIndex(int index) const;
    inline sf::Vector2f getGridSize() { return m_grid_size; }
    void removeTile(const sf::Vector2f& position);
    bool isPositionOccupied(const sf::Vector2f& position) const;
    void snapTileMapTiles();
    void clearTiles();
    struct TileInfo {
        int id;
        sf::Vector2f position;
        sf::Sprite sprite;
    };

    std::vector<TileInfo> m_tiles;
    TileData& tile_data;
    std::vector<uint32_t> m_tileIDs;
    int m_width;
    int m_height;
    sf::Vector2f m_grid_size;
    int opacity = 255;
    sf::Sprite createSprite(int id, const sf::Vector2f& position);

    std::vector<sf::FloatRect> getTileHitboxes() const {
        std::vector<sf::FloatRect> hitboxes;

        for (const auto& tile : m_tiles) {
            sf::FloatRect hitbox = tile.sprite.getGlobalBounds();
            hitbox.left = tile.position.x;
            hitbox.top = tile.position.y;
            hitboxes.push_back(hitbox);
        }

        return hitboxes;
    }

private:
    sf::Color m_tint = sf::Color::White;

};

#endif // TILE_MAP_HPP