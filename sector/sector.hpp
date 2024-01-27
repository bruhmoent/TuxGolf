//  TuxGolf
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

#include "LevelData.hpp"
#include "jsonParser.hpp"
#include "tileData.hpp"
#include "tileMaps.hpp"
#include "tileMap.hpp"

#ifndef SECTOR_HPP
#define SECTOR_HPP

class Sector {
public:
    Sector(const std::string& file_path, float x, float y, const sf::Vector2f& gridSize)
        : m_gridSize(gridSize) {
        sector_size.x = x;
        sector_size.y = y;

        m_file_path = file_path;
        m_tile_data = JsonParser::loadTileData(m_file_path);

        tile_ids = m_tile_data.getTileIDs();

        for (int id : tile_ids) {
            m_tile_data.addTexturePath(id, m_tile_data.getTexturePath(id));
        }
    }

    void displayTileMaps(sf::RenderWindow& window) {
        tileMaps.draw(window);
    }

    const std::vector<TileMap*> getTileMaps() const {
        return tileMaps.m_tileMaps;
    }

    sf::Vector2u get_sector_size() { return sector_size; }

    void load_level(const std::string& levelFilePath, sf::Vector2u& levelSize) {
        try {
            m_levelData.loadLevel(levelFilePath, m_gridSize, levelSize, m_tile_data, tileMaps);

            for (TileMap* tmPtr : tileMaps.m_tileMaps) {
                if (tmPtr) {
                    TileMap& tm = *tmPtr;
                    tm.snapTileMapTiles();
                }
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Exception occurred while loading level: " << e.what() << std::endl;
            std::cout << "Tried to load:" << levelFilePath << std::endl;
        }
    }

private:
    std::string m_file_path = "";
    sf::Vector2u sector_size;
    sf::Vector2f m_gridSize;
    TileData m_tile_data;
    std::vector<int> tile_ids;
    LevelData m_levelData;
    TileMaps tileMaps;
};

#endif // SECTOR_HPP