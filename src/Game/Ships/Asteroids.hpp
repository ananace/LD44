#pragma once

#include "../CogShape.hpp"
#include "../Ship.hpp"

#include <SFML/Graphics/ConvexShape.hpp>

namespace Game
{
namespace Ships
{

class Asteroids : public Ship
{
public:
    Asteroids();

    virtual float getRadius() const override;
    virtual void update(float aDt) override;

private:
    void drawShape(sf::RenderTarget& aTarget, sf::RenderStates aStates) const override;

    sf::ConvexShape m_shipShape;
    CogShape m_centerCog;
    CogShape m_frontCog;
};

}
}
