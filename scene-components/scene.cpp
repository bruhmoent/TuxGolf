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

#include "scene.hpp"

void Scene::add_music_object(MusicObject* music) {
    m_music_objects.push_back(music);
}

void Scene::add_background(Background* background) {
    m_background_objects.push_back(background);
}

void Scene::add_menu(Menu* menu) {
    m_menu_objects.push_back(menu);
}

void Scene::song()
{
    if(m_music_objects.size() > 0)
    m_music_objects[0]->play();
}

void Scene::handle_ev(sf::RenderWindow& window) {
    for (auto& menu : m_menu_objects) {
        if (menu) {
            if (menu->check_buttons_input(window)) {
            }
        }
    }
}

void Scene::stop_music()
{
    if(m_music_objects.size() > 0)
        m_music_objects[0]->stop();
}

void Scene::draw(sf::RenderWindow& window) {
    handleCollisions();

    for (const auto& background : m_background_objects) {
        if (background) {
            background->draw(window);

            if (background->scroll_enabled == true)
                background->scroll(window.getSize().x);
        }
    }

    if (m_sectors.size() > 0)
    {
        displaySectors(window);
    }

    if (m_entities.size() > 0)
    {
        //Temporary, the first entity will be always the player, right now its an enemy.
        camera->viewFollow({ m_entities[0]->x, m_entities[0]->y }, window, 3.f);
    }

    for (const auto& entity : m_entities) {
        if (entity) {
            entity->draw(window, *entityTextures);
            entity->update();
        }
    }
}