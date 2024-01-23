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

#ifndef TILEMAP_HPP
#define TILEMAP_HPP

struct Tile;
struct Tiles;

struct 
TileMap
{

    int opacity = 255;
    std::vector<Tile*> m_tileMapTiles;
    std::vector<Tile*> m_helperMapTiles;
    sf::Vector2f m_gridSize = { 0.f, 0.f };

    TileMap(const sf::Vector2f& gridSize)
        : m_gridSize(gridSize) {
    }

    //Change size of tiles
    void setTileSize(const sf::Vector2f& tileSize);

    //Add a tile to a tilemap
    void addTile(Tile* tile, Tiles& tiles);

    //Tint a tilemap
    void tintTiles(sf::Color tintColour);

    //Set opacity of a tilemap
    void setOpacity(int value);

    //Draw the tilemap
    void draw(sf::RenderWindow& window);

    //Display the tiles
    void displayTiles(sf::RenderWindow& window);

    //Set the size of the grid on a tilemap
    void setGrid(const sf::Vector2f& gridSize);

    //Snap tiles to grid
    void snapTileMapTiles();

};

#endif // TILEMAP_HPP