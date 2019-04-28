#include "Attachement.hpp"
#include "Hardpoint.hpp"
#include "Mount.hpp"
#include "Weapon.hpp"

using Game::Attachement;
using Game::Hardpoint;
using Game::Mount;
using Game::Weapon;

const Hardpoint* Attachement::getMountpoint() const
{
    return m_hardpoint;
}

sf::Vector2f Attachement::getGlobalPosition()
{
    if (m_hardpoint)
        return m_hardpoint->getGlobalPosition();
    return {};
}
const sf::Vector2f& Attachement::getGlobalTargetPosition()
{
    static const sf::Vector2f emptyTarget;
    if (m_hardpoint)
        return m_hardpoint->getParent()->getTargetPosition();
    return emptyTarget;
}
float Attachement::getGlobalDirection()
{
    if (m_hardpoint)
        return m_hardpoint->getGlobalDirection();
    return 0.f;
}

Mount& Attachement::asMount()
{
    return *static_cast<Mount*>(this);
}
const Mount& Attachement::asMount() const
{
    return *static_cast<const Mount*>(this);
}
Weapon& Attachement::asWeapon()
{
    return *static_cast<Weapon*>(this);
}
const Weapon& Attachement::asWeapon() const
{
    return *static_cast<const Weapon*>(this);
}
