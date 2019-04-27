#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transform.hpp>

namespace Game
{

class HardpointOwner
{
public:
    virtual const sf::Transform& getTransform() const = 0;
    virtual const sf::Vector2f& getPosition() const = 0;
    virtual float getRotation() const = 0;
};

}
