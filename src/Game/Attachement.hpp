#pragma once

#include <SFML/System/Vector2.hpp>

#include <cstdint>

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
    virtual int8_t getClass() const { return 1; }

    virtual void update(float aDt) { }

    virtual sf::Vector2f getGlobalPosition();
    virtual const sf::Vector2f& getGlobalTargetPosition();
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
