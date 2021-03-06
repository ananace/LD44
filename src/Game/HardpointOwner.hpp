#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transform.hpp>

#include <cstdint>

namespace Game
{

class HardpointOwner
{
public:
    virtual const sf::Transform& getTransform() const = 0;
    virtual const sf::Vector2f& getPosition() const = 0;
    virtual const sf::Vector2f& getVelocity() const = 0;
    virtual const sf::Vector2f& getTargetPosition() const = 0;
    virtual float getRotation() const = 0;

    virtual uint8_t getCollisionMask() const = 0;
    virtual uint8_t getTargetCollisionMask() const = 0;
};

}
