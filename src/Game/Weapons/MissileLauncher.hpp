#pragma once

#include "../Weapon.hpp"
#include "../../Projectile.hpp"

#include <array>
#include <memory>
#include <cstdint>

namespace Game
{
namespace Weapons
{

class MissileLauncher : public Weapon
{
public:
    MissileLauncher();

    virtual void update(float aDt) override;
    virtual bool canFire() const override;
    virtual void fire() override;

private:
    float m_reload, m_burnTime;
    std::weak_ptr<Projectile> m_missile;
};

}
}
