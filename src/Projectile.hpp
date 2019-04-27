#pragma once

#include "Collider.hpp"

class Projectile : public Collider
{
public:
    Projectile();
    Projectile(uint8_t aMask, float aLifetime, float aRadius, const sf::Vector2f& aPosition, float aDirection, float aVelocity);

    sf::Vector2f Position;
    float Lifetime, Direction, Velocity, Radius;
    uint8_t CollisionMask;

    virtual uint8_t getCollisionMask() const override;
    virtual const sf::Vector2f& getPosition() const override;
    virtual float getRadius() const override;
    virtual bool onCollision(const Collider* aOther) override;
};

