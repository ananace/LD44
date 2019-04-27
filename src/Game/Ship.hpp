#pragma once

#include "Hardpoint.hpp"
#include "Mount.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <functional>
#include <deque>

namespace Game
{

class Hardpoint;
class Weapon;

class Ship : public Mount, public sf::Drawable, public sf::Transformable
{
public:
    Ship();
    ~Ship() = default;

    virtual float getRadius() const;

    void draw(sf::RenderTarget& aTarget, sf::RenderStates aStates) const override;

protected:
    virtual void drawShape(sf::RenderTarget& aTarget, sf::RenderStates aStates) const;

private:

};

}
