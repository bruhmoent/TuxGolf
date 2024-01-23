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

#include "menu_util.hpp"

#include "../ui-components/menu.hpp"

MenuUtil::MenuUtil() {}

MenuUtil::~MenuUtil()
{
    clear_stack();
}

void MenuUtil::clear_stack()
{
    bool able = true;
    for (const auto& menu : m_menu_stack)
    {
        if (!menu)
        {
            able = false;
        }
    }

    if(able)
        m_menu_stack.clear();
}

void MenuUtil::add_menu(Menu* menu)
{
    m_menu_stack.push_back(menu);
}

void MenuUtil::stop_menu(Menu* menu)
{
    if (menu && menu->m_is_active)
        menu->m_is_active = false;
    else
        std::cerr << "Cannot access null ptr or menu is already inactive!\n";
}

void MenuUtil::draw_menus(sf::RenderWindow& window)
{
    for (const auto& menu : m_menu_stack)
    {
        if (menu && menu->m_is_active)
            menu->draw(window);
    }
}

void MenuUtil::menu_handle_inputs(sf::RenderWindow& window)
{
    for (const auto& menu : m_menu_stack)
    {
        if (menu && menu->m_is_active)
            menu->check_buttons_input(window);
    }
}

void MenuUtil::make_menu_active(Menu* menu)
{
    if (menu)
        menu->m_is_active = true;
    else
        std::cerr << "Cannot read a null ptr.\n";
}