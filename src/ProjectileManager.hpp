#pragma once

#include "Projectile.hpp"

#include <deque>
#include <memory>

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

    std::weak_ptr<Projectile> addProjectile(uint8_t aMask, float aLifetime, float aRadius, const sf::Vector2f& aPosition, float aDirection, float aVelocity);
    void update(float aDt);
    void draw(sf::RenderTarget& aTarget);

private:
    std::deque<std::shared_ptr<Projectile>> m_projectiles;
    uint8_t m_iter;
};
