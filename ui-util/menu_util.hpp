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

class Menu;

#ifndef MENU_UTIL_HPP
#define MENU_UTIL_HPP

#include <SFML/Graphics.hpp>
#include <vector>

template <typename T>
struct has_get_width {
    template <typename C>
    static constexpr auto test(int) -> decltype(std::declval<C>().get_width(), std::true_type{});

    template <typename>
    static constexpr std::false_type test(...);

    static constexpr bool value = decltype(test<T>(0))::value;
};

template <typename T>
struct has_get_height {
    template <typename C>
    static constexpr auto test(int) -> decltype(std::declval<C>().get_height(), std::true_type{});

    template <typename>
    static constexpr std::false_type test(...);

    static constexpr bool value = decltype(test<T>(0))::value;
};

template <typename T>
struct has_get_background_color {
    template <typename C>
    static constexpr auto test(int) -> decltype(std::declval<C>().get_background_color(), std::true_type{});

    template <typename>
    static constexpr std::false_type test(...);

    static constexpr bool value = decltype(test<T>(0))::value;
};

template <typename T>
struct has_get_background_rect {
    template <typename C>
    static constexpr auto test(int) -> decltype(std::declval<C>().get_background_rect(), std::true_type{});

    template <typename>
    static constexpr std::false_type test(...);

    static constexpr bool value = decltype(test<T>(0))::value;
};

template <typename T>
struct has_get_position {
    template <typename C>
    static constexpr auto test(int) -> decltype(std::declval<C>().get_position(), std::true_type{});

    template <typename>
    static constexpr std::false_type test(...);

    static constexpr bool value = decltype(test<T>(0))::value;
};

class MenuUtil
{
public:
    MenuUtil();

    ~MenuUtil();

    void clear_stack();

    void add_menu(Menu* menu);

    void stop_menu(Menu* menu);

    void draw_menus(sf::RenderWindow& window);

    template <typename T>
    void add_bg_to_element(T* t) {
        if (!t) {
            std::cerr << "Error: Invalid pointer to add_bg_to_element.\n";
            return;
        }

        sf::RectangleShape rect;

        // Check if T has the get_background_color function
        if constexpr (has_get_background_color<T>::value) {
            rect.setFillColor(t->get_background_color());
        }
        else {
            std::cerr << "T doesn't have a get_background_color function.\n";
        }

        // Check if T has the get_menu_width and get_menu_height functions
        if constexpr (has_get_width<T>::value && has_get_height<T>::value) {
            rect.setSize(sf::Vector2f(t->get_width(), t->get_height()));
        }
        else {
            std::cerr << "T doesn't have get_width or get_height functions.\n";
        }

        // Check if T has the get_position function
        if constexpr (has_get_position<T>::value) {
            rect.setPosition(t->get_position());
        }
        else {
            std::cerr << "T doesn't have a get_position function.\n";
        }

        // Check if T has the set_background_rect function
        if constexpr (std::is_member_function_pointer<decltype(&T::set_background_rect)>::value) {
            t->set_background_rect(rect);
        }
        else {
            std::cerr << "T doesn't have a set_background_rect function.\n";
        }
    }

    template <typename T>
    void add_image_to_element(T* t, const std::string& texture_path) {
        if (!t) {
            std::cerr << "Error: Invalid pointer to add_image_to_element.\n";
            return;
        }

        sf::Sprite* sprite = new sf::Sprite;
        sf::Texture* texture = new sf::Texture;
        texture->setRepeated(true);
        if (!texture->loadFromFile(texture_path)) {
            std::cerr << "Error: Failed to load texture from file: " << texture_path << "\n";
            delete texture;
            return;
        }
        sprite->setTexture(*texture);

        // Check if T has the get_menu_width and get_menu_height functions
        if constexpr (has_get_width<T>::value && has_get_height<T>::value) {
            sprite->setScale(sf::Vector2f(t->get_width() / texture->getSize().x, t->get_height() / texture->getSize().y));
        }
        else {
            std::cerr << "T doesn't have get_width or get_height functions.\n";
        }

        // Check if T has the get_position function
        if constexpr (has_get_position<T>::value) {
            sprite->setPosition(t->get_position());
        }
        else {
            std::cerr << "T doesn't have a get_position function.\n";
        }

        // Check if T has the set_background_rect function
        if constexpr (std::is_member_function_pointer<decltype(&T::set_background_sprite)>::value) {
            t->set_background_sprite(sprite);
        }
        else {
            std::cerr << "T doesn't have a set_background_sprite function.\n";
        }
    }

    template <typename T>
    void change_element_background_texture(T* t, const std::string& texture_path) {
        if (!t) {
            std::cerr << "Error: Invalid pointer to change_element_background_texture.\n";
            return;
        }

        sf::Sprite* sprite = new sf::Sprite;
        sf::Texture* texture = new sf::Texture;
        texture->setRepeated(true);
        if (!texture->loadFromFile(texture_path)) {
            std::cerr << "Error: Failed to load texture from file: " << texture_path << "\n";
            delete texture;
            return;
        }
        sprite->setTexture(*texture);

        // Check if T has the get_menu_width and get_menu_height functions
        if constexpr (has_get_width<T>::value && has_get_height<T>::value) {
            sprite->setScale(sf::Vector2f(t->get_width() / texture->getSize().x, t->get_height() / texture->getSize().y));
        }
        else {
            std::cerr << "T doesn't have get_width or get_height functions.\n";
        }

        // Check if T has the get_position function
        if constexpr (has_get_position<T>::value) {
            sprite->setPosition(t->get_position());
        }
        else {
            std::cerr << "T doesn't have a get_position function.\n";
        }

        // Check if T has the set_background_sprite function
        if constexpr (std::is_member_function_pointer<decltype(&T::set_background_sprite)>::value) {
            t->set_background_sprite(sprite);
        }
        else {
            std::cerr << "T doesn't have a set_background_sprite function.\n";
        }
    }

    void make_menu_active(Menu* menu);

    std::vector<Menu*>::iterator find_menu(Menu* menu);

    void menu_handle_inputs(sf::RenderWindow& window);

private:
    std::vector<Menu*> m_menu_stack;
};

#endif // MENU_UTIL_HPP