//  LevelEditor
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
#include "entity_textures.hpp"

#ifndef ENTITY_HPP
#define ENTITY_HPP

class Entity {
public:
    float x = 0.f;
    float y = 0.f;
    float vel_x = 0.f;
    float vel_y = 0.f;
    float initialY = 0.f;
    float initialX = 0.f;

    virtual ~Entity() = default;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window, EntityTextures& entityTextures) = 0;

    virtual bool selfVsEntity(Entity& other) {
        return getHitbox().intersects(other.getHitbox());
    }

    virtual bool selfVsTile(const sf::FloatRect& tileRect) {
        return getHitbox().intersects(tileRect);
    }

    virtual sf::FloatRect getHitbox() const {
        return hitbox;
    }

    virtual void setHitboxX(float _x) {
        hitbox.left = _x;
    }

    virtual void setHitboxY(float _y) {
        hitbox.top = _y;
    }

    virtual void setHitbox(sf::FloatRect& _hitbox)
    {
        hitbox = _hitbox;
    }

    virtual void on_hit_signal(const sf::FloatRect& otherHitbox) = 0;
    int collisionGroup = 0;

private:
    bool collisionHandled = false;
    sf::FloatRect hitbox;
};

#endif // ENTITY_HPP