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

#include "scene_manager.hpp"

void SceneManager::add_scene(Scene* scene) {
    m_scenes.push_back(scene);
}

void SceneManager::delete_scene(const std::string& sceneName) {
    m_scenes.erase(std::remove_if(m_scenes.begin(), m_scenes.end(),
        [&sceneName](Scene* scene) {
            return scene->get_name() == sceneName;
        }),
        m_scenes.end());
}

void SceneManager::pass_music(const std::string& sceneName) {
    for (auto& scene : m_scenes) {
        if (scene->get_name() == sceneName) {
            scene->song();
            break;
        }
    }
}

void SceneManager::stop_all_music()
{
    for (auto& scene : m_scenes) {
            scene->stop_music();
    }
}

void SceneManager::bring_to_front(const std::string& sceneName) {
    for (auto it = m_scenes.begin(); it != m_scenes.end(); ++it) {
        if ((*it)->get_name() == sceneName) {
            std::rotate(m_scenes.begin(), it, it + 1);
            break;
        }
    }

    for (int i = 0; i < m_scenes.size(); i++) {
        if (m_scenes[i]->m_menu_objects.size() > 0) {
            for (int j = 0; j < m_scenes[i]->m_menu_objects.size(); j++) {
                m_scenes[i]->m_menu_objects[j]->m_is_active = (i == 0);
            }
        }

        m_scenes[i]->reset_entities();
    }
}

void SceneManager::draw_current_scene(sf::RenderWindow& window) {
   m_scenes[0]->draw(window);

   for (const auto& menu : m_scenes[0]->m_menu_objects) {
       if (menu) {
           menu->draw(window);
       }
   }
}

void SceneManager::handle_input(sf::RenderWindow& window) {
    if (!m_scenes.empty()) {
        m_scenes.front()->handle_ev(window);
    }
}