#pragma once

#include <SFML/System/Vector2.hpp>

namespace Game
{

class Hardpoint;
class Mount;
class Weapon;

class Attachement
{
public:
    const Hardpoint* getMountpoint() const;

    virtual bool isMount() const { return false; }
    virtual bool isWeapon() const { return false; }

    virtual void update(float aDt) { }

    virtual sf::Vector2f getGlobalPosition();
    virtual float getGlobalDirection();

    Mount& asMount();
    const Mount& asMount() const;
    Weapon& asWeapon();
    const Weapon& asWeapon() const;

private:
    friend class Hardpoint;

    Hardpoint* m_hardpoint;
};

}
