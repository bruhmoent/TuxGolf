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

#include <SFML/Graphics.hpp>
#include <unordered_map>

#ifndef ENTITY_TEXTURES_HPP
#define ENTITY_TEXTURES_HPP

class EntityTextures {
public:
    std::unordered_map<std::string, sf::Texture> textureMap;

    void loadTexture(const std::string& path) {
        sf::Texture texture;
        texture.loadFromFile(path);
        textureMap[path] = texture;
    }

    sf::Texture& getTexture(const std::string& path) {
        return textureMap[path];
    }
};

#endif // ENTITY_TEXTURES_HPP