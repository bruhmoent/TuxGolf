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

#include "tileMaps.hpp"
#include "tileMap.hpp"

void
TileMaps::addTileMap(const TileMap& tileMap) {
	m_tileMaps.push_back(new TileMap(tileMap));
}

void
TileMaps::setActive(int index) {
	if (index >= 0 && index < m_tileMaps.size()) {
		m_activeTileMapIndex = index;
	}
}

void TileMaps::displayLayering(sf::RenderWindow& window) {
	for (TileMap* tileMap : m_tileMaps) {
		if (tileMap == m_tileMaps[m_activeTileMapIndex]) {
			tileMap->setOpacity(255);
		}
		else {
			tileMap->setOpacity(128);
		}
	}
}

void
TileMaps::displayAllTiles(sf::RenderWindow& window) {
	for (TileMap* tileMap : m_tileMaps) {
		tileMap->displayTiles(window);
	}
}

int
TileMaps::getCurrentTileMapIndex() {
	return m_activeTileMapIndex;
}

TileMap*
TileMaps::getCurrentTileMap() {
	return m_tileMaps[m_activeTileMapIndex];
}

const sf::Vector2f&
TileMaps::getCurrentGridSize() {
	return m_tileMaps[m_activeTileMapIndex]->m_gridSize;
}