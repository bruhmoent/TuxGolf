//  AcornUI
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

#include "text_object.hpp"

void TextObject::set_text(std::string text)
{
	m_text.setString(text);
}

void TextObject::set_position(float x, float y)
{
	m_text.setPosition(x, y);
}

void TextObject::set_color(int r, int g, int b)
{
	m_text.setFillColor(sf::Color(r, g, b));
}

void TextObject::set_size(int size)
{
	m_text.setCharacterSize(size);
}

sf::FloatRect TextObject::get_local_bounds() const
{
	return m_text.getLocalBounds();
}

const sf::Text& TextObject::get_text() const
{
	return m_text;
}

const sf::Font& TextObject::get_font() const
{
	return m_font;
}