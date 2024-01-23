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

#ifndef TILEMAPS_HPP
#define TILEMAPS_HPP

struct TileMap;

struct 
TileMaps    
{

    std::vector<TileMap*> m_tileMaps;
    int m_activeTileMapIndex = 0;

    //Add a tilemap to the tilemaps' struct
    void addTileMap(const TileMap& tileMap);

    //Set the current active tilemap
    void setActive(int index);

    //Display layering effect
    void displayLayering(sf::RenderWindow& window);

    //Displays all tiles
    void displayAllTiles(sf::RenderWindow& window);

    //Get current active tilemap
    TileMap* getCurrentTileMap();

    //Get current active grid size
    const sf::Vector2f& getCurrentGridSize();

    //Get current active index
    int getCurrentTileMapIndex();

};

#endif //TILEMAPS_HPP