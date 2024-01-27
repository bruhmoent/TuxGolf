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
#include "../sector/camera.hpp"
#include "../entity/concrete_entity_factory.hpp"
#include "../entity/entity.hpp"
#include "../collision/collision_method.hpp"
#include "../collision/quad_tree.hpp"

enum EntityType {
    INVALID_TYPE = -1,
    SOLDIER = 0
};

class Scene {
public:
    Scene(const std::string& name) : m_name(name) {
        entityFactoryMap[SOLDIER] = new ConcreteEntityFactory<Soldier>();
        entityTextures = new EntityTextures();
        camera = new Camera();

        collisionMethod = new CollisionMethod();

        collisionMethod->addCollisionGroup("group1");
        collisionMethod->addCollisionGroup("group2");

        sf::FloatRect quadtreeBounds(0.0f, 0.0f, 800, 600);
        int maxQuadtreeLevels = 5;
        quadtree = new Quadtree(quadtreeBounds, 0, maxQuadtreeLevels);
    }

    void add_music_object(MusicObject* music);
    void add_background(Background* background);
    void add_menu(Menu* menu);
    void draw(sf::RenderWindow& window);
    void song();
    void stop_music();
    void handle_ev(sf::RenderWindow& window);

    void reset_entities() {
        for (auto& entity : m_entities) {
            entity->x = entity->initialX;
            entity->y = entity->initialY;
            entity->vel_x = 0.f;
            entity->vel_y = 0.f;
        }
    }

    void handleCollisions() {
        updateQuadtree();

        for (const auto& pair : collisionMethod->collisionCallbacks) {
            const std::string& group = pair.first;
            collisionMethod->checkCollisions(group);
        }

        for (const auto& sector : m_sectors) {
            const auto& tileMaps = sector->getTileMaps();

            for (const auto& entity : m_entities) {
                std::vector<sf::FloatRect> collisionTiles;

                for (const auto& tileMap : tileMaps) {
                    auto tileHitboxes = tileMap->getTileHitboxes();
                    collisionTiles.insert(collisionTiles.end(), tileHitboxes.begin(), tileHitboxes.end());
                }

                quadtree->retrieveTilesInRange(*entity, collisionTiles);

                for (const auto& tile : collisionTiles) {
                    if (entity->selfVsTile(tile)) {
                        entity->on_hit_signal(tile);
                    }
                }
            }
        }
    }

    void add_texture_path(const std::string& path) {
        if (entityTextures) {
            if (entityTextures->textureMap.find(path) == entityTextures->textureMap.end()) {
                entityTextures->loadTexture(path);
            }
        }
    }

    template <typename T>
    EntityType get_entity_type() {
        if (std::is_same<T, Soldier>::value) {
            return SOLDIER;
        }
        return INVALID_TYPE;
    }

    template <typename T>
    void add_entity(const std::string& path) {
        Entity* newEntity = nullptr;

        auto factoryIt = entityFactoryMap.find(get_entity_type<T>());
        if (factoryIt != entityFactoryMap.end()) {
            newEntity = factoryIt->second->create(path);
        }
        else {
            std::cerr << "Invalid EntityType\n";
            return;
        }

        if (newEntity) {
            m_entities.push_back(newEntity);
        }

        add_texture_path(path);
    }

    template <typename T>
    void add_type_entity(const std::string& path) {
        add_entity<T>(path);
    }

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

        for (auto& entity : m_entities) {
            delete entity;
        }
        m_entities.clear();

        for (auto& pair : entityFactoryMap) {
            delete pair.second;
        }

        delete entityTextures;
        delete camera;
        delete collisionMethod;
        delete quadtree;
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
    EntityTextures* entityTextures;
    std::vector<MusicObject*> m_music_objects;
    std::vector<Background*> m_background_objects;
    std::string m_name;

    std::vector<Entity*> m_entities;
    std::unordered_map<EntityType, EntityFactory*> entityFactoryMap;
    Camera* camera;

    CollisionMethod* collisionMethod;
    Quadtree* quadtree;

    void updateQuadtree() {
        quadtree->clear();

        for (const auto& entity : m_entities) {
            quadtree->insert(*entity);
        }
    }
};

#endif // SCENE_HPP