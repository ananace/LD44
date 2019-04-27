#pragma once

#include "../Weapon.hpp"

#include <array>
#include <cstdint>

namespace Game
{
namespace Weapons
{

class Gun : public Weapon
{
public:
    Gun();

    virtual void update(float aDt) override;

    // virtual bool requiresReload() const override;
    virtual bool canFire() const override;
    virtual void fire() override;

private:
    float m_reload,
          m_cooldown;
    std::size_t m_ammunition;
};

}
}
