#pragma once

#include "Projectile.hpp"

#include <deque>

namespace sf { class RenderTarget; }

class ProjectileManager
{
public:
    enum
    {
        kMaxProjectiles = 256,
        kCleanupInterval = 10
    };

    ProjectileManager();

    void addProjectile(uint8_t aMask, float aLifetime, float aRadius, const sf::Vector2f& aPosition, float aDirection, float aVelocity);
    void update(float aDt);
    void draw(sf::RenderTarget& aTarget);

private:
    std::deque<Projectile> m_projectiles;
    uint8_t m_iter;
};
