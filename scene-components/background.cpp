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

#include "background.hpp"

Background::Background(const std::string& path, float x, float y, float scroll_x, float scroll_y, bool scrl_enabled)
    : m_x(x), m_y(y), m_scroll_x(scroll_x), m_scroll_y(scroll_y), scroll_enabled(scrl_enabled)
{
    sf::Texture* texture = new sf::Texture;
    texture->setSmooth(true);
    texture->setRepeated(true);

    if (!texture->loadFromFile(path)) {
        delete texture;
        std::cerr << "Failed to load texture: " << path << std::endl;
        return;
    }

    m_bg_sprite1.setTexture(*texture);
    m_bg_sprite2.setTexture(*texture);

    m_bg_sprite1.setPosition(m_x, m_y);
    m_bg_sprite2.setPosition(m_x + m_bg_sprite1.getTexture()->getSize().x, m_y);
}

void Background::draw(sf::RenderWindow& window)
{
    sf::View oldView = window.getView();

    window.setView(window.getDefaultView());

    window.draw(m_bg_sprite1);
    window.draw(m_bg_sprite2);

    window.setView(oldView);
}

void Background::scroll(float window_width) 
{
        m_x += m_scroll_x;
        m_y += m_scroll_y;

        m_bg_sprite1.setPosition(m_x, m_y);
        m_bg_sprite2.setPosition(m_x + m_bg_sprite1.getGlobalBounds().width, m_y);

        if (m_bg_sprite1.getPosition().x > 0 && m_bg_sprite1.getPosition().x > window_width) {
            m_x = -m_bg_sprite1.getGlobalBounds().width;
            m_bg_sprite1.setPosition(m_x, m_y);
        }

        if (m_bg_sprite2.getPosition().x > 0 && m_bg_sprite2.getPosition().x > window_width) {
            m_x = m_bg_sprite1.getPosition().x - m_bg_sprite2.getGlobalBounds().width;
            m_bg_sprite2.setPosition(m_x + m_bg_sprite1.getGlobalBounds().width, m_y);
        }
}