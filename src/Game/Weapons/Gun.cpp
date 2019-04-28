#include "Gun.hpp"
#include "../../Application.hpp"

#include <algorithm>

#include <cstdio>

using Game::Weapons::Gun;

Gun::Gun()
    : m_reload(0.f)
    , m_cooldown(0.f)
    , m_ammunition(8)
{
}

void Gun::update(float aDt)
{
    m_reload = std::max(0.f, m_reload - aDt);
    m_cooldown = std::max(0.f, m_cooldown - aDt);
}

bool Gun::canFire() const
{
    return m_reload <= 0.f && m_cooldown <= 0.f;
}

void Gun::fire()
{
    if (!canFire())
        return;

    if (m_ammunition == 0)
    {
        printf("Gun[%p]: Reload!\n", this);

        m_reload = 2.5f;
        m_ammunition = 8;
        return;
    }

    printf("Gun[%p]: Pew!\n", this);

    Application::getApplication().getProjectileManager().addProjectile(
        CollisionMask_ALL_Enemy,
        5.f, 1.f, getGlobalPosition(), getGlobalDirection(), 500.f
    );

    m_ammunition--;
    m_cooldown = 0.5f;
}
