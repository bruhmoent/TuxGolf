// Quadtree.hpp

#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "../entity/entity.hpp"

class Quadtree {
public:
    Quadtree(sf::FloatRect bounds, int level, int maxLevels);

    void clear();
    void insert(Entity& entity);
    void retrieveCollisions(Entity& entity, std::vector<Entity*>& collisionEntities);
    void retrieveTilesInRange(const Entity& entity, std::vector<sf::FloatRect>& collisionTiles);

private:
    static const int MAX_ENTITIES_PER_NODE = 10;

    sf::FloatRect bounds;
    int level;
    int maxLevels;
    std::vector<Entity*> entities;
    Quadtree* nodes[4];

    bool isLeafNode() const;
    void split();
    int getIndex(const Entity& entity) const;
};

#endif // QUADTREE_HPP
