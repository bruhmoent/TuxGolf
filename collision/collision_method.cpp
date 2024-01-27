#include "collision_method.hpp"

void CollisionMethod::addCollisionGroup(const std::string& group) {
    collisionGroups[group] = std::vector<Entity*>();
}

void CollisionMethod::addCollisionCallback(const std::string& group1, const std::string& group2, CollisionCallback callback) {
    collisionCallbacks[group1][group2] = callback;
    collisionCallbacks[group2][group1] = callback;
}

void CollisionMethod::checkCollisions(const std::string& group) {
    auto it1 = collisionGroups.find(group);
    if (it1 != collisionGroups.end()) {
        auto& entities1 = it1->second;

        for (Entity* entity1 : entities1) {
            for (const auto& pair : collisionCallbacks[group]) {
                const std::string& otherGroup = pair.first;
                auto it2 = collisionGroups.find(otherGroup);
                if (it2 != collisionGroups.end()) {
                    auto& entities2 = it2->second;

                    for (Entity* entity2 : entities2) {
                        if (entity1->selfVsEntity(*entity2)) {
                            pair.second(*entity1, *entity2);
                        }
                    }
                }
            }
        }
    }
}
