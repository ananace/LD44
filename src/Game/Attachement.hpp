#pragma once

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

    Mount& asMount();
    const Mount& asMount() const;
    Weapon& asWeapon();
    const Weapon& asWeapon() const;

private:
    friend class Hardpoint;

    Hardpoint* m_hardpoint;
};

}
