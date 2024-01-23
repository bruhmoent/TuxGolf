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

#include "../ui-util/directives.hpp"

#ifndef MENU_ITEM_HPP
#define MENU_ITEM_HPP

class TextObject;

class MenuItem
{
public:
	MenuItem(const std::string& label, float margin_x, float margin_y);
	virtual ~MenuItem();

	virtual void draw(sf::RenderWindow& window);

	virtual float get_distance() const { return 0.f;  }

	virtual float get_width() const { return m_width; }

	virtual float get_height() const { return m_height; }

	sf::Color get_background_color();

	sf::RectangleShape get_background_rect();

	sf::Sprite* get_background_sprite();

	sf::Vector2f get_position();

	void set_position(float x, float y);

	void set_background_sprite(sf::Sprite* sprite);

	void set_background_rect(const sf::RectangleShape& rect);

	void set_background_color(const sf::Color& color);

	void set_width(const float width);

	void set_height(const float height);
	 
protected:
	float m_height;
	float m_width;

	std::unique_ptr<TextObject> m_text_object;
	sf::RectangleShape m_background_shape;
	sf::Sprite* m_background_sprite = nullptr;
	sf::Color m_background_color = sf::Color::White;

	sf::Vector2f m_pos = { 0.f, 0.f };
};

#endif // MENU_ITEM_HPP