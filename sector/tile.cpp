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

#include "tile.hpp"

void
Tile::setSize(const sf::Vector2f& size)
{
	m_shape.setSize(size);
	m_sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
}

void
Tile::tint(const sf::Color& tintColour)
{
	m_sprite.setColor(tintColour);
}