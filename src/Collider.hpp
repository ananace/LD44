#pragma once

#include <SFML/System/Vector2.hpp>
#include <cstdint>

enum CollisionMasks : uint8_t
{
    CollisionMask_PlayerShip = 1 << 0,
    CollisionMask_PlayerBullet = 1 << 1,
    CollisionMask_EnemyShip = 1 << 2,
    CollisionMask_EnemyBullet = 1 << 3,

    CollisionMask_NONE = 0,
    CollisionMask_ALL_Player = CollisionMask_PlayerBullet | CollisionMask_PlayerShip,
    CollisionMask_ALL_Enemy = CollisionMask_EnemyBullet | CollisionMask_EnemyShip,
    CollisionMask_ALL = 0xFF
};

class CollisionManager;

class Collider
{
public:
    virtual ~Collider();

    virtual uint8_t getCollisionMask() const = 0;
    virtual const sf::Vector2f& getPosition() const = 0;
    virtual float getRadius() const = 0;

protected:
    virtual bool onCollision(const Collider* aOther) = 0;

private:
    friend class CollisionManager;
};
