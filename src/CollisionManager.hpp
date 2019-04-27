#pragma once

#include "Collider.hpp"
#include <deque>

class CollisionManager
{
public:
    void update(float aDt);

    void clear();
    void addCollider(Collider* aCollider);
    void removeCollider(Collider* aCollider);

private:
    std::deque<Collider*> m_colliders;
};
