#ifndef COLLISION_METHOD_HPP
#define COLLISION_METHOD_HPP

#include <functional>
#include <unordered_map>
#include <vector>
#include "../entity/entity.hpp"

class CollisionMethod {
public:
    using CollisionCallback = std::function<void(Entity&, Entity&)>;

    void addCollisionGroup(const std::string& group);

    void addCollisionCallback(const std::string& group1, const std::string& group2, CollisionCallback callback);

    void checkCollisions(const std::string& group);

    std::unordered_map<std::string, std::vector<Entity*>> collisionGroups;

    std::unordered_map<std::string, std::unordered_map<std::string, CollisionCallback>> collisionCallbacks;
};

#endif // COLLISION_METHOD_HPP
