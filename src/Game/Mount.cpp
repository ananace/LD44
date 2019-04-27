#include "Mount.hpp"
#include "Hardpoint.hpp"
#include "Weapon.hpp"

using Game::Hardpoint;
using Game::Mount;
using Game::Weapon;

std::size_t Mount::getHardpointCount() const
{
    return m_hardpoints.size();
}
Hardpoint& Mount::getHardpoint(std::size_t aId)
{
    return m_hardpoints.at(aId);
}
const Hardpoint& Mount::getHardpoint(std::size_t aId) const
{
    return m_hardpoints.at(aId);
}

void Mount::visitHardpoints(const std::function<void(Hardpoint&)>& aMethod)
{
    for (auto& point : m_hardpoints)
    {
        if (point.hasAttachement() && point.getAttachement().isMount())
            point.getAttachement().asMount().visitHardpoints(aMethod);
        aMethod(point);
    }
}
void Mount::visitHardpoints(const std::function<void(const Hardpoint&)>& aMethod) const
{
    for (auto& point : m_hardpoints)
    {
        if (point.hasAttachement() && point.getAttachement().isMount())
            point.getAttachement().asMount().visitHardpoints(aMethod);
        aMethod(point);
    }
}
void Mount::visitWeapons(const std::function<void(Weapon&)>& aMethod)
{
    for (auto& point : m_hardpoints)
    {
        if (!point.hasAttachement())
            continue;
        auto& attachement = point.getAttachement();
        if (attachement.isMount())
            attachement.asMount().visitWeapons(aMethod);
        else
            aMethod(attachement.asWeapon());
    }
}
void Mount::visitWeapons(const std::function<void(const Weapon&)>& aMethod) const
{
    for (auto& point : m_hardpoints)
    {
        if (!point.hasAttachement())
            continue;
        auto& attachement = point.getAttachement();
        if (attachement.isMount())
            attachement.asMount().visitWeapons(aMethod);
        else
            aMethod(attachement.asWeapon());
    }
}

void Mount::addHardpoint(const Hardpoint& aHardpoint)
{
    m_hardpoints.push_back(aHardpoint);
}
void Mount::addHardpoint(Hardpoint&& aHardpoint)
{
    m_hardpoints.emplace_back(std::move(aHardpoint));
}
