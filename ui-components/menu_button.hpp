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
#include "menu_item.hpp"

#ifndef MENU_BUTTON_HPP
#define MENU_BUTTON_HPP

class TextObject;
class ActionDictionary;

class MenuButton : public MenuItem
{
public:
    MenuButton(const std::string& label, float margin_x, float margin_y, std::function<void()> action_func = {});
    virtual ~MenuButton();

    virtual bool on_actions(const ActionDictionary& dictionary);
    bool handle_mouse_click(sf::RenderWindow& window);

private:
    std::function<void()> m_action_func;
    bool m_was_pressed = false;
    bool m_hover = false;
    float m_hover_progress = 0.0f;

    sf::Color on_normal = sf::Color::White;
    sf::Color on_hover = sf::Color(230, 230, 230, 255);

    sf::FloatRect get_item_bounds() const;
    sf::Color interpolateColors(const sf::Color& color1, const sf::Color& color2, float progress);
};

#endif // MENU_BUTTON_HPP