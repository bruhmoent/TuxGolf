//  TuxGolf
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
#include <iostream>

#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

class Background
{
public:
	Background(const std::string& path, float x, float y, float scroll_x = 0.f, float scroll_y = 0.f, bool scrl_enabled = false);
	~Background() {}

	void draw(sf::RenderWindow& window);
	void scroll(float window_width);

	bool scroll_enabled = false;
private:
	sf::Sprite m_bg_sprite1;
	sf::Sprite m_bg_sprite2;
	float m_x;
	float m_y;
	float m_scroll_x;
	float m_scroll_y;
};

#endif