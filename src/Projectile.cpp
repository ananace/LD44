#include "Projectile.hpp"

Projectile::Projectile()
    : Position()
    , Lifetime(0.f)
    , Direction(0.f)
    , Velocity(0.f)
    , Radius(0.f)
    , CollisionMask(CollisionMask_NONE)
{
}
Projectile::Projectile(uint8_t aMask, float aLifetime, float aRadius, const sf::Vector2f& aPosition, float aDirection, float aVelocity)
    : Position(aPosition)
    , Lifetime(aLifetime)
    , Direction(aDirection)
    , Velocity(aVelocity)
    , Radius(aRadius)
    , CollisionMask(aMask)
{
}

uint8_t Projectile::getCollisionMask() const
{
    return CollisionMask;
}
const sf::Vector2f& Projectile::getPosition() const
{
    return Position;
}
float Projectile::getRadius() const
{
    return Radius;
}
bool Projectile::onCollision(const Collider* aOther)
{
    Lifetime = 0;

    return false;
}
