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

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#ifndef SCENE_HPP
#define SCENE_HPP

#include "music_object.hpp"
#include "background.hpp"
#include "../ui-components/menu.hpp"
#include "../sector/sector.hpp"

class Scene {
public:
    Scene(const std::string& name) : m_name(name) {}

    void add_music_object(MusicObject* music);
    void add_background(Background* background);
    void add_menu(Menu* menu);
    void draw(sf::RenderWindow& window);
    void song();
    void stop_music();
    void handle_ev(sf::RenderWindow& window);

    const std::string& get_name() const { return m_name; }

    ~Scene() {
        for (auto& music : m_music_objects) {
            delete music;
        }
        m_music_objects.clear();

        for (auto& background : m_background_objects) {
            delete background;
        }
        m_background_objects.clear();

        for (auto& sector : m_sectors) {
            delete sector;
        }
        m_sectors.clear();

        m_menu_objects.clear();
    }

    void add_sector(Sector* sector) {
        m_sectors.push_back(sector);
    }

    void displaySectors(sf::RenderWindow& window) {
        for (Sector* sector : m_sectors) {
            sector->displayTileMaps(window);
        }
    }

    std::vector<Menu*> m_menu_objects;
    std::string last_scene = "";

private:
    std::vector<Sector*> m_sectors;
    std::vector<MusicObject*> m_music_objects;
    std::vector<Background*> m_background_objects;
    std::string m_name;
};

#endif // SCENE_HPP