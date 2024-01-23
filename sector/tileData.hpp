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

#ifndef TILEDATA_HPP
#define TILEDATA_HPP

struct Tile;

struct 
TileData {

    std::unordered_map<int, std::string> m_texturePaths;

    //Bind a path to an ID
    void addTexturePath(int id, const std::string& texturePath);

    //Get path by ID
    const std::string& getTexturePath(int id) const;

    //Get IDs of the tiles
    std::vector<int> getTileIDs() const;

};

#endif // TILEDATA_HPP