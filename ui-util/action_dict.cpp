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

#include "action_dict.hpp"

void ActionDictionary::mapAction(const std::string& actionName, sf::Keyboard::Key key) {
    actions[actionName] = { key, false, false };
}

void ActionDictionary::update() {
    for (auto& action : actions) {
        if (sf::Keyboard::isKeyPressed(action.second.key)) {
            action.second.isPressed = true;
            action.second.isHeld = true;
        }
        else {
            action.second.isPressed = false;
            action.second.isHeld = false;
        }
    }
}

bool ActionDictionary::isActionPressed(const std::string& actionName) const {
    auto it = actions.find(actionName);
    if (it != actions.end()) {
        return it->second.isPressed;
    }
    return false;
}

bool ActionDictionary::isActionHeld(const std::string& actionName) const {
    auto it = actions.find(actionName);
    if (it != actions.end()) {
        return it->second.isHeld;
    }
    return false;
}