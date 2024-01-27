// Quadtree.cpp

#include "quad_tree.hpp"

Quadtree::Quadtree(sf::FloatRect bounds, int level, int maxLevels)
    : bounds(bounds), level(level), maxLevels(maxLevels) {
    for (int i = 0; i < 4; ++i) {
        nodes[i] = nullptr;
    }
}

void Quadtree::clear() {
    for (int i = 0; i < 4; ++i) {
        if (nodes[i] != nullptr) {
            nodes[i]->clear();
            delete nodes[i];
            nodes[i] = nullptr;
        }
    }

    if (!entities.empty()) {
        entities.clear();
    }
}

void Quadtree::insert(Entity& entity) {
    if (isLeafNode()) {
        if (entities.size() < MAX_ENTITIES_PER_NODE || level >= maxLevels) {
            entities.push_back(&entity);
            return;
        }

        split();
    }

    int index = getIndex(entity);

    if (index != -1) {
        nodes[index]->insert(entity);
    }
}

void Quadtree::retrieveCollisions(Entity& entity, std::vector<Entity*>& collisionEntities) {
    for (int i = 0; i < 4; ++i) {
        if (nodes[i] != nullptr && nodes[i]->bounds.intersects(entity.getHitbox())) {
            nodes[i]->retrieveCollisions(entity, collisionEntities);
        }
    }

    for (const auto& otherEntity : entities) {
        if (otherEntity->collisionGroup == entity.collisionGroup) {
            collisionEntities.push_back(otherEntity);
        }
    }
}

bool Quadtree::isLeafNode() const {
    return nodes[0] == nullptr;
}

void Quadtree::split() {
    float subWidth = bounds.width / 2.0f;
    float subHeight = bounds.height / 2.0f;
    float x = bounds.left;
    float y = bounds.top;

    for (int i = 0; i < 4; ++i) {
        float childX = x + (i % 2) * subWidth;
        float childY = y + (i / 2) * subHeight;

        nodes[i] = new Quadtree(sf::FloatRect(childX, childY, subWidth, subHeight), level + 1, maxLevels);
    }

    for (auto& currentEntity : entities) {
        int index = getIndex(*currentEntity);
        if (index != -1) {
            nodes[index]->insert(*currentEntity);
        }
    }

    entities.clear();
}

void Quadtree::retrieveTilesInRange(const Entity& entity, std::vector<sf::FloatRect>& collisionTiles) {
    if (!isLeafNode()) {
        for (int i = 0; i < 4; ++i) {
            if (nodes[i] != nullptr && nodes[i]->bounds.intersects(entity.getHitbox())) {
                nodes[i]->retrieveTilesInRange(entity, collisionTiles);
            }
        }
    }
}

int Quadtree::getIndex(const Entity& entity) const {
    int index = -1;
    double verticalMidpoint = bounds.left + (bounds.width / 2.0);
    double horizontalMidpoint = bounds.top + (bounds.height / 2.0);

    bool topQuadrant = (entity.y + entity.getHitbox().height < horizontalMidpoint);
    bool bottomQuadrant = (entity.y > horizontalMidpoint);

    if (entity.x + entity.getHitbox().width < verticalMidpoint) {
        if (topQuadrant) {
            index = 0; // Top-left quadrant
        }
        else if (bottomQuadrant) {
            index = 2; // Bottom-left quadrant
        }
    }
    else if (entity.x > verticalMidpoint) {
        if (topQuadrant) {
            index = 1; // Top-right quadrant
        }
        else if (bottomQuadrant) {
            index = 3; // Bottom-right quadrant
        }
    }

    return index;
}