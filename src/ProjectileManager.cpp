#include "ProjectileManager.hpp"
#include "Util.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <algorithm>

#include <cmath>

ProjectileManager::ProjectileManager()
    : m_iter(0)
{
}

std::weak_ptr<Projectile> ProjectileManager::addProjectile(uint8_t aMask, float aLifetime, float aRadius, const sf::Vector2f& aPosition, float aDirection, float aVelocity)
{
    if (m_projectiles.size() >= kMaxProjectiles)
        return {};

    m_projectiles.emplace_back(std::make_shared<Projectile>(aMask, aLifetime, aRadius, aPosition, aDirection * Deg2Rad(), aVelocity));
    return {m_projectiles.back()};
}

void ProjectileManager::update(float aDt)
{
    ++m_iter;

    for (auto& proj : m_projectiles)
    {
        proj->Lifetime -= aDt;
        if (proj->Lifetime <= 0)
            continue;

        proj->Position += sf::Vector2f(cos(proj->Direction) * proj->Velocity * aDt, sin(proj->Direction) * proj->Velocity * aDt);
    }

    // Only cleanup old projectiles occasionally
    if (m_iter % kCleanupInterval == 0)
    {
        auto it = std::remove_if(m_projectiles.begin(), m_projectiles.end(), [](auto& proj) { return proj->Lifetime <= 0; });
        if (it != m_projectiles.end())
            m_projectiles.erase(it, m_projectiles.end());
    }
}

void ProjectileManager::draw(sf::RenderTarget& aTarget)
{
    sf::CircleShape bullet;
    bullet.setFillColor(sf::Color::Transparent);
    bullet.setOutlineColor(sf::Color(255, 255, 0));
    bullet.setOutlineThickness(1.f);

    for (auto& proj : m_projectiles)
    {
        bullet.setRadius(proj->Radius);
        bullet.setOrigin(proj->Radius, proj->Radius);
        bullet.setPosition(proj->Position);

        aTarget.draw(bullet);
    }
}
