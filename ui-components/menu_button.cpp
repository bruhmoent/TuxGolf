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

#include "menu_button.hpp"
#include "../ui-util/action_dict.hpp"

MenuButton::MenuButton(const std::string& label, float margin_x, float margin_y, std::function<void()> action_func)
    : MenuItem(label, margin_x, margin_y), m_action_func(action_func) {}

MenuButton::~MenuButton() {}

bool MenuButton::on_actions(const ActionDictionary& dictionary) {
    if (dictionary.isActionPressed("Select")) {
        if (m_action_func) {
            m_action_func();
        }
        return true;
    }
    return false;
}

bool MenuButton::handle_mouse_click(sf::RenderWindow& window) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    sf::Vector2f mouse_pos_view = window.mapPixelToCoords(mouse_pos);

    sf::FloatRect item_bounds(m_pos.x, m_pos.y, m_width, m_height);

    if (item_bounds.contains(mouse_pos_view)) {
        if (!m_hover) {
            m_hover = true;
            m_hover_progress = 0.0f; // Initialize the hover progress
        }

        if (m_hover_progress < 1.0f) {
            m_hover_progress += 0.15f; // Adjust the fade speed as needed
        }

        sf::Color current_color = interpolateColors(sf::Color::White, on_hover, m_hover_progress);
        if (m_background_sprite) {
            m_background_sprite->setColor(current_color);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (!m_was_pressed) {
                m_was_pressed = true;
                m_action_func();
                return true;
            }
        }
        else {
            m_was_pressed = false;
        }
    }
    else {
        if (m_hover) {
            m_hover = false;
            m_hover_progress = 1.0f; // Initialize the hover progress for fade out

            sf::Color current_color = interpolateColors(on_hover, sf::Color::White, m_hover_progress);
            if (m_background_sprite) {
                m_background_sprite->setColor(current_color);
            }
        }

        if (m_hover_progress > 0.0f) {
            m_hover_progress -= 0.15f; // Adjust the fade speed as needed
        }
    }

    return false;
}

sf::Color MenuButton::interpolateColors(const sf::Color& color1, const sf::Color& color2, float progress) {
    sf::Uint8 r = static_cast<sf::Uint8>(color1.r + (color2.r - color1.r) * progress);
    sf::Uint8 g = static_cast<sf::Uint8>(color1.g + (color2.g - color1.g) * progress);
    sf::Uint8 b = static_cast<sf::Uint8>(color1.b + (color2.b - color1.b) * progress);
    sf::Uint8 a = static_cast<sf::Uint8>(color1.a + (color2.a - color1.a) * progress);

    return sf::Color(r, g, b, a);
}