#ifndef SOLDIER_HPP
#define SOLDIER_HPP

#include "../entity.hpp"
#include <cmath>

class Soldier : public Entity {
public:
    std::string e_texture_path;
    bool collisionOccurred = false;

    Soldier(const std::string& texturePath)
        : e_texture_path(texturePath) {
        x = 300.f;
        y = 200.f;
        initialX = x;
        initialY = y;
        sf::FloatRect _f(x, y, 64.f, 64.f);
        setHitbox(_f);
    }

    void update() override {
        vel_x += 0.0f;
        vel_y += 0.9f;

        x = initialX + vel_x;
        y += vel_y;

        setHitboxX(x);
        setHitboxY(y);
    }

    void on_hit_signal(const sf::FloatRect& otherHitbox) override {
        if (selfVsTile(otherHitbox)) {
           
        }

        setHitboxX(x);
        setHitboxY(y);
    }

    void draw(sf::RenderWindow& window, EntityTextures& entityTextures) override {
        sf::Sprite sprite(entityTextures.getTexture(e_texture_path));
        sprite.setPosition(x, y);
        window.draw(sprite);

        sf::RectangleShape hitboxShape(sf::Vector2f(getHitbox().width, getHitbox().height));
        hitboxShape.setPosition(x + getHitbox().left, y + getHitbox().top);
        hitboxShape.setFillColor(sf::Color(255, 0, 0, 100));
        window.draw(hitboxShape);
    }

};

#endif // SOLDIER_HPP
