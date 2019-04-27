#include "CollisionManager.hpp"
#include "Collider.hpp"

#include <algorithm>

void CollisionManager::update(float aDt)
{
    // TODO: Improve
    for (auto it = m_colliders.begin(); it != m_colliders.end(); ++it)
    {
        uint8_t aCollMask = (*it)->getCollisionMask();
        for (auto it2 = it + 1; it2 != m_colliders.end(); ++it2)
        {
            uint8_t bCollMask = (*it2)->getCollisionMask();
            if ((aCollMask & bCollMask) == 0)
                continue;

            auto& aPos = (*it)->getPosition();
            auto aRad = (*it)->getRadius();
            auto& bPos = (*it2)->getPosition();
            auto bRad = (*it2)->getRadius();

            auto diff = bPos - aPos;
            auto dist = diff.x * diff.x + diff.y * diff.y;
            if (dist < aRad * aRad + bRad * bRad)
            {
                (*it)->onCollision(*it2);
                (*it2)->onCollision(*it);
            }
        }
    }
}

void CollisionManager::clear()
{
    m_colliders.clear();
}
void CollisionManager::addCollider(Collider* aCollider)
{
    m_colliders.emplace_back(aCollider);
}
void CollisionManager::removeCollider(Collider* aCollider)
{
    auto it = std::find(m_colliders.cbegin(), m_colliders.cend(), aCollider);
    if (it != m_colliders.cend())
        m_colliders.erase(it);
}
