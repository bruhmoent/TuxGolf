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

#include "../entity.hpp"
#include <cmath>

#ifndef SOLDIER_HPP
#define SOLDIER_HPP

class Soldier : public Entity {
public:
    std::string e_texture_path;
    float time = 0.0;
    float initialY = 0.0;
    const float amplitude = 20.f;
    const float frequency = 0.3f;

    Soldier(const std::string& texturePath)
        : e_texture_path(texturePath) {
        hitbox.width = 30.0;
        hitbox.height = 30.0;
    }

    void update() override {
        time += 0.1;

        // Oscillate the y position using sine function.
        y = initialY + amplitude * std::sin(frequency * time);

    }

    void draw(sf::RenderWindow& window, EntityTextures& entityTextures) override {
        sf::Sprite sprite(entityTextures.getTexture(e_texture_path));
        sprite.setPosition(x, y);
        window.draw(sprite);
    }
};

#endif // SOLDIER_HPP