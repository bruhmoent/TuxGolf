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

#include "ui-components/menu_item.hpp"
#include "ui-components/menu_button.hpp"
#include "ui-util/menu_util.hpp"
#include "scene-components/scene_manager.hpp"
#include "external-util/editorLog.hpp"

#ifndef APP_HPP
#define APP_HPP

class App {
public:
    ~App() {
        if (m_sc_manager) {
            delete m_sc_manager;
            m_sc_manager = nullptr;
        }
        if (window) {
            delete window;
            window = nullptr;
        }

        for (auto& item : m_items)
        {
            delete item;
        }
    }

    App(std::string title, uint32_t width, uint32_t height, std::string app_icon)
        //FIXME: Temporary code.

        : m_app_title(title), m_app_icon(app_icon) {
        window = new sf::RenderWindow(sf::VideoMode(width, height), title);
        window->setFramerateLimit(60);

        sf::Image icon;
        Background *m_bg = new Background("data/assets/scene/forest_panorama.png", 0.f, 0.f, 0.1f, 0.0f, true);
        Background* world1_bg = new Background("data/assets/scene/world1.png", 0.f, 0.f);
        Background* fog = new Background("data/assets/scene/fog.png", 0.f, 0.f, 0.6f, 0.0f, true);

        //Level themes

        auto main_theme = new MusicObject("data/music/main_menu.ogg");
        auto world1_theme = new MusicObject("data/music/world1.ogg");
        auto level1_theme = new MusicObject("data/music/forest2.ogg");

        // Scenes
        auto menu_scene = new Scene("main-menu");
        auto level_scene = new Scene("level-scene");
        auto loaded_level = new Scene("level");

        m_sc_manager = new SceneManager(&m_menuManager);
        EditorLog editorLog(*window, "data/app/system.ttf");
        std::string last_scene = "level-scene";
        std::vector<sf::Vector2f> itemPositions = {
        {73.f, -10.f},
        {391.f, 38.f},
        {652.f, 166.f},
        {518.f, 219.f},
        {364.f, 292.f},
        {133.f, 344.f}
        };

        // Menu scene init.
        sf::Vector2f main_pos(250.f, 150.f);
        sf::Vector2f back_pos(15.f, 500.f);
        sf::Vector2f title_pos(220.f, 30.f);
        sf::Vector2f w1_title_pos(600.f, -20.f);

        auto back = new Menu(back_pos, true, false);
        back->set_menu_height(64.f);
        back->set_menu_width(128.f);
        back->set_background_color(sf::Color(0, 0, 0, 0));

        auto mainMenu = new Menu(main_pos, true, false);
        mainMenu->set_menu_height(100.f);
        mainMenu->set_menu_width(300.f);
        mainMenu->set_background_color(sf::Color(0, 0, 0, 0));

        auto menu_title = new Menu(title_pos, true, false);
        menu_title->set_menu_height(90.f);
        menu_title->set_menu_width(362.0f);
        menu_title->set_background_color(sf::Color(0, 0, 0, 0));

        auto w1_title = new Menu(w1_title_pos, true, false);
        w1_title->set_menu_height(120.f);
        w1_title->set_menu_width(200.0f);
        w1_title->set_background_color(sf::Color(0, 0, 0, 0));

        m_menuManager.add_bg_to_element(mainMenu);
        m_menuManager.add_bg_to_element(menu_title);
        m_menuManager.add_bg_to_element(w1_title);
        m_menuManager.add_bg_to_element(back);

        mainMenu->add_string_button("Story", [this]() {
            std::cout << "Story\n";
            m_sc_manager->stop_all_music();
            m_sc_manager->bring_to_front("level-scene");
            m_sc_manager->pass_music("level-scene");
            });

        mainMenu->add_string_button("Settings", []() { std::cout << "Settings\n"; });
        mainMenu->add_string_button("Quit", []() { std::cout << "Quit\n"; });

        back->add_string_button("Back", [this]() {
            std::cout << "Back\n";
            m_sc_manager->stop_all_music();
            m_sc_manager->bring_to_front("main-menu");
            m_sc_manager->pass_music("main-menu");
            });

        m_menuManager.add_image_to_element(mainMenu, "menu.png");
        m_menuManager.add_image_to_element(menu_title, "data/assets/tuxgolf-logo.png");
        m_menuManager.add_image_to_element(w1_title, "data/assets/scene/world_title1.png");

        for (auto& itemPtr : mainMenu->m_items) {
            itemPtr->set_background_color(sf::Color(0, 0, 0, 0));
            m_menuManager.add_image_to_element(itemPtr, "log_frame.png");
            m_menuManager.add_bg_to_element(itemPtr);
        }

        for (auto& itemPtr : back->m_items) {
            itemPtr->set_background_color(sf::Color(0, 0, 0, 0));
            m_menuManager.add_image_to_element(itemPtr, "data/assets/level_menu/level_square_last.png");
            m_menuManager.add_bg_to_element(itemPtr);
        }

        m_menuManager.add_menu(mainMenu);
        m_menuManager.add_menu(menu_title);
        m_menuManager.add_menu(w1_title);


        menu_scene->add_background(m_bg);
        menu_scene->add_music_object(main_theme);
        menu_scene->add_menu(mainMenu);
        menu_scene->add_menu(menu_title);

        level_scene->add_background(world1_bg);
        level_scene->add_background(fog);
        level_scene->add_music_object(world1_theme);

        Sector* sector = new Sector("example/tileSchema.json", 2000, 600, sf::Vector2f(64.f, 64.f));

        loaded_level->add_sector(sector);
        loaded_level->add_music_object(level1_theme);

        auto back_level = new Menu(back_pos, true, false);
        back_level->set_menu_height(64.f);
        back_level->set_menu_width(128.f);
        back_level->set_background_color(sf::Color(0, 0, 0, 0));

        m_menuManager.add_bg_to_element(back_level);

        back_level->add_string_button("Back", [this, last_scene]() {
            std::cout << "Back to last: " << last_scene << "\n";
            m_sc_manager->stop_all_music();
            m_sc_manager->bring_to_front(last_scene);
            m_sc_manager->pass_music(last_scene);
            });

        for (auto& itemPtr : back_level->m_items) {
            itemPtr->set_background_color(sf::Color(0, 0, 0, 0));
            m_menuManager.add_image_to_element(itemPtr, "data/assets/level_menu/level_square_last.png");
            m_menuManager.add_bg_to_element(itemPtr);
        }

        loaded_level->add_menu(back_level);

        for (int i = 0; i < 6; i++)
        {
            Item* item = new Item(itemPositions[i]);

            switch (i)
            {
            case 0:
                item->is_active = true;
                break;
            case 2:
                item->is_boss = true;
            default:
                break;
            }

            item->create_item(i + 1, level_scene, m_menuManager, m_sc_manager, sector);
            m_items.push_back(item);
        }


        Item* item = new Item(itemPositions[5]);
        item->create_item(6, level_scene, m_menuManager, m_sc_manager, sector);
        m_items.push_back(item);

        m_items[0]->is_active = true;

        m_menuManager.add_menu(back);

        level_scene->add_menu(back);
        level_scene->add_menu(w1_title);

        m_sc_manager->add_scene(menu_scene);
        m_sc_manager->add_scene(level_scene);
        m_sc_manager->add_scene(loaded_level);

        if (icon.loadFromFile(m_app_icon)) {
            window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        }

        for (int i = 0; i < m_items.size() - 1; i++)
        {
            m_menuManager.add_menu(m_items[i]->i_menu);
            level_scene->add_menu(m_items[i]->i_menu);
            m_items[i]->update(m_menuManager);
        }

        m_sc_manager->pass_music("main-menu");
        m_sc_manager->bring_to_front("main-menu");
    }   

    void app_loop();

    sf::RenderWindow* window;

private:
    std::string m_app_title = "";
    std::string m_app_icon = "";
    SceneManager* m_sc_manager;
    MenuUtil m_menuManager;

    class Item
    {
    public:
        Item(sf::Vector2f pos, bool active = false) : is_active(active), i_pos(pos), i_menu(new Menu(i_pos, true, true)) 
        {
        }

        bool is_completed = false;
        bool is_active = false;
        bool is_boss = false;

        std::string bg_path = "data/assets/level_menu/level_square_locked.png";
        sf::Vector2f i_pos;
        Menu* i_menu;

        void update(MenuUtil& m_manag)
        {
            if (is_boss && is_active) {
                bg_path = "data/assets/level_menu/level_square_boss.png";
            }
            else if (is_active) {
                bg_path = "data/assets/level_menu/level_square.png";
            }
            if (is_completed) {
               bg_path = "data/assets/level_menu/level_square_completed.png";
            }

            m_manag.change_element_background_texture(this->i_menu->m_items[0], bg_path);
        }

        void create_item(int index, Scene* scene, MenuUtil& m_manag, SceneManager* m_sc_manager, Sector* sector)
        {
            i_menu->m_is_active = false;
            i_menu->multiplier = 0.75f;
            i_menu->set_menu_height(128.f);
            i_menu->set_menu_width(128.f);
            i_menu->set_background_color(sf::Color(0, 0, 0, 0));

            if (is_active) {
                bg_path = "data/assets/level_menu/level_square.png";
            }
            if (is_boss) {
                bg_path = "data/assets/level_menu/level_square_boss_locked.png";
            }
            if (is_boss && is_active) {
                bg_path = "data/assets/level_menu/level_square_boss.png";
            }

            m_manag.add_bg_to_element(i_menu);

            std::string action = "level" + std::to_string(index) + ".json";
            i_menu->add_string_button(std::to_string(index), [action, this, m_sc_manager, sector]() {
                if (this->is_active) {
                    sf::Vector2u _tmp(2000, 600);
                    this->is_completed = true;
                    m_sc_manager->stop_all_music();
                    sector->load_level(action, _tmp);
                    m_sc_manager->bring_to_front("level");
                    m_sc_manager->pass_music("level");
                }
                });

            i_menu->m_items[0]->set_background_color(sf::Color(0, 0, 0, 0));
            m_manag.add_image_to_element(i_menu->m_items[0], bg_path);
            m_manag.add_bg_to_element(i_menu->m_items[0]);

        }
    };

    std::vector<Item*> m_items;
};

#endif