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

#include <string>
#include <vector>

#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include "scene.hpp"
#include "../ui-util/menu_util.hpp"

class SceneManager {
public:
    SceneManager(MenuUtil* menu_manager) : m_menuManager(menu_manager) {}
    ~SceneManager() {
        for (auto& scene : m_scenes) {
            delete scene;
        }
    }

    void add_scene(Scene* scene);
    void delete_scene(const std::string& scene_name);
    void bring_to_front(const std::string& scene_name);
    void draw_current_scene(sf::RenderWindow& window);
    void handle_input(sf::RenderWindow& window);
    void pass_music(const std::string& scene_name);
    void stop_all_music();

private:
    std::vector<Scene*> m_scenes;
    MenuUtil* m_menuManager;
};

#endif // SCENE_MANAGER_HPP