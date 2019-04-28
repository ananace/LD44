#pragma once

#include "Attachement.hpp"
#include "Hardpoint.hpp"

#include <functional>
#include <deque>

namespace Game
{

class Weapon;

class Mount : public Attachement
{
public:
    virtual bool isMount() const override { return true; }

    std::size_t getHardpointCount() const;
    Hardpoint& getHardpoint(std::size_t aId);
    const Hardpoint& getHardpoint(std::size_t aId) const;

    void visitHardpoints(const std::function<void(Hardpoint&)>& aMethod);
    void visitHardpoints(const std::function<void(const Hardpoint&)>& aMethod) const;
    void visitWeapons(const std::function<void(Weapon&)>& aMethod);
    void visitWeapons(const std::function<void(const Weapon&)>& aMethod) const;

protected:
    void addHardpoint(const Hardpoint& aHardpoint);
    void addHardpoint(Hardpoint&& aHardpoint);

private:
    std::deque<Hardpoint> m_hardpoints;
};

}
