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

#include <SFML/Window/Keyboard.hpp>
#include <unordered_map>
#include <vector>

#ifndef ACTION_DICT_HPP
#define ACTION_DICT_HPP

class ActionDictionary {
public:
    struct Action {
        sf::Keyboard::Key key;
        bool isPressed = false;
        bool isHeld = false;
    };

    void mapAction(const std::string& actionName, sf::Keyboard::Key key);

    void update();

    bool isActionPressed(const std::string& actionName) const;

    bool isActionHeld(const std::string& actionName) const;

private:
    std::unordered_map<std::string, Action> actions;
};

#endif // ACTION_DICT_HPP