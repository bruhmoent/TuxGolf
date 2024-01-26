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

#ifndef LEVELDATA_HPP
#define LEVELDATA_HPP

#include <string>
#include <fstream>
#include <iostream>
#include "tileData.hpp"
#include "tileMaps.hpp"

class LevelData {
public:
    void saveLevel(const std::string& levelName, const sf::Vector2u& levelSize, const sf::Vector2f& gridSize, TileData& tileData, TileMaps& tileMaps);
    void loadLevel(const std::string& filePath, const sf::Vector2f& gridSize, sf::Vector2u& levelSize, TileData& tileData, TileMaps& tileMaps);
};

#endif // LEVELDATA_HPP