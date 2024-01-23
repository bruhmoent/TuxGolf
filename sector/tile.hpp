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

#ifndef TILE_HPP
#define TILE_HPP

struct 
Tile {

    sf::Sprite m_sprite;
    sf::RectangleShape m_shape;
    sf::Vector2f m_position;
    int m_onTileMapID = 0;
    int m_ID;

    Tile(sf::Sprite sprite = sf::Sprite(), sf::RectangleShape shape = sf::RectangleShape(), sf::Vector2f position = sf::Vector2f(), int ID = 0)
        : m_sprite(sprite), m_shape(shape), m_position(position), m_ID(ID)
    {
        m_sprite.setPosition(m_position);
    }

    //Set the size of the tile
    void setSize(const sf::Vector2f& size);

    //Tint a tile
    void tint(const sf::Color& tintColour);

};

#endif // TILE_HPP