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