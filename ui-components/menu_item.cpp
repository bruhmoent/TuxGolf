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

#include "menu_item.hpp"

#include "../ui-assets/text_object.hpp"

MenuItem::MenuItem(const std::string& label, float width, float height) : m_width(width), m_height(height)
{
	m_text_object = std::make_unique<TextObject>(label, 0, 0, 20, 255, 255, 255);
	m_text_object->set_text(label);
	m_text_object->set_position(m_pos.x, m_pos.y);
}

MenuItem::~MenuItem()
{
	delete m_background_sprite;
}

void MenuItem::draw(sf::RenderWindow& window)
{
	if (m_background_shape.getGlobalBounds().width > 0 && m_background_shape.getGlobalBounds().height > 0) {
		window.draw(m_background_shape);
	}

	if (m_background_sprite && m_background_sprite->getGlobalBounds().width > 0 && m_background_sprite->getGlobalBounds().height > 0) {
		window.draw(*m_background_sprite);
	}

	window.draw(m_text_object->get_text());
}

void MenuItem::set_position(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
	float offsetX = (m_width - m_text_object->get_local_bounds().width) / 2;
	float offsetY = (m_height - m_text_object->get_local_bounds().height) / 2;

	// Set the position of the text object with the offset
	m_text_object->set_position(m_pos.x + offsetX, m_pos.y + offsetY);
}

void MenuItem::set_background_sprite(sf::Sprite* sprite)
{
	m_background_sprite = sprite;
}

sf::Color MenuItem::get_background_color()
{
	return m_background_color;
}

sf::RectangleShape MenuItem::get_background_rect()
{
	return m_background_shape;
}

sf::Sprite* MenuItem::get_background_sprite()
{
	return m_background_sprite;
}

sf::Vector2f MenuItem::get_position()
{
	return m_pos;
}

void MenuItem::set_background_rect(const sf::RectangleShape& rect)
{
	m_background_shape = rect;
}

void MenuItem::set_background_color(const sf::Color& color)
{
	m_background_color = color;
}

void MenuItem::set_width(const float width)
{
	m_width = width;
}

void MenuItem::set_height(const float height)
{
	m_height = height;
}