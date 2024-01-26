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

#include "tileMaps.hpp"

TileMaps::~TileMaps() {
    for (auto tileMap : m_tileMaps) {
        delete tileMap;
    }
}

void TileMaps::draw(sf::RenderWindow& window)
{
    for (auto& tileMap : m_tileMaps)
    {
        tileMap->draw(window);
    }
}

void TileMaps::addTileMap(const TileMap& tileMap) {
    TileMap* newTileMap = new TileMap(tileMap.tile_data, tileMap.m_width, tileMap.m_height, tileMap.m_grid_size);
    newTileMap->m_tiles = tileMap.m_tiles;
    m_tileMaps.push_back(newTileMap);
}

void TileMaps::setActive(int index) {
    if (index >= 0 && index < m_tileMaps.size()) {
        activeTileMapIndex = index;
    }
}

void TileMaps::snapTileMapTiles()
{
    for (auto& tm : m_tileMaps)
    {
        tm->snapTileMapTiles();
    }
}

TileMap* TileMaps::getCurrentTileMap() {
    if (activeTileMapIndex >= 0 && activeTileMapIndex < m_tileMaps.size()) {
        return m_tileMaps[activeTileMapIndex];
    }
    return nullptr;
}

const sf::Vector2f& TileMaps::getCurrentGridSize() {
    TileMap* currentTileMap = getCurrentTileMap();
    if (currentTileMap) {
        return currentTileMap->getGridSize();
    }
    static sf::Vector2f defaultGridSize(0.f, 0.f);
    return defaultGridSize;
}

int TileMaps::getCurrentTileMapIndex() {
    return activeTileMapIndex;
}