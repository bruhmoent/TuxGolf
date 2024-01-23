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

#include "directives.hpp"

#ifndef TILES_HPP
#define TILES_HPP

struct TileMaps;
struct TileData;
struct Tile;

struct
Tiles {

    std::vector<Tile*> m_tiles;

    //Add a tile to a tilemap
    void addTileToTileMap(const TileData& tileData, int id, const sf::Vector2f& mousePosition, const sf::Vector2f& gridSize, const sf::Vector2u& levelSize, TileMaps& tileMaps, int tileMapID);

    //Remove tile
    void removeTile(const sf::Vector2f& position);

    //Snaps tiles to a grid
    void snapAllTilesToGrid(const sf::Vector2f& gridSize);

    //Iterate though the tiles vector and check for position overlap
    bool isPositionOccupied(const sf::Vector2f& position) const;
    
    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> m_textureDictionary;
};

#endif // TILES_HPP