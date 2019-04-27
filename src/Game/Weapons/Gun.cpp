#include "Gun.hpp"

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
        m_reload = 2.5f;
        m_ammunition = 8;
        return;
    }

    printf("Pew!\n");

    m_ammunition--;
    m_cooldown = 0.5f;
}
