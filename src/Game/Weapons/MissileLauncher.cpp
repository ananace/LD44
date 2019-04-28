#include "MissileLauncher.hpp"
#include "../Mount.hpp"
#include "../../Application.hpp"
#include "../../Spinor.hpp"
#include "../../Util.hpp"

#include <cmath>

using Game::Weapons::MissileLauncher;

MissileLauncher::MissileLauncher()
    : m_reload(0)
    , m_burnTime(0)
{
}

void MissileLauncher::update(float aDt)
{
    m_reload = std::max(0.f, m_reload - aDt);
    if (m_missile.expired())
        return;

    m_burnTime = std::max(0.f, m_burnTime - aDt);
    if (m_burnTime <= 0)
        return;

    auto missile = m_missile.lock();
    auto& target = getGlobalTargetPosition();
    float targetDir = getDirection(missile->Position, target);
    float curDir = missile->Direction;

    float diff = Spinor::slerpAngle(curDir, targetDir, aDt * 2);
    missile->Direction = diff;
}
bool MissileLauncher::canFire() const
{
    return m_reload <= 0 && m_missile.expired();
}
void MissileLauncher::fire()
{
    if (!canFire())
        return;

    m_missile = Application::getApplication().getProjectileManager().addProjectile(
        CollisionMask_ALL_Enemy,
        5.f, 1.f, getGlobalPosition(), getGlobalDirection(), 250.f
    );

    m_burnTime = 2.f;
    m_reload = 2.5f;
}
