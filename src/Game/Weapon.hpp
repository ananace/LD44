#pragma once

#include "Attachement.hpp"

namespace Game
{

class Hardpoint;

class Weapon : public Attachement
{
public:
    virtual bool isWeapon() const override { return true; }

private:
};

}
