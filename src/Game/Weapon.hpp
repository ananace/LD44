#pragma once

#include "Attachement.hpp"

namespace Game
{

class Hardpoint;

class Weapon : public Attachement
{
public:
    virtual bool isWeapon() const override { return true; }

    // virtual bool isContinuousFire() const { return false; }
    // virtual bool requiresReload() const { return false; }

    virtual bool canFire() const { return true; }
    virtual void fire() = 0;

private:
};

}
