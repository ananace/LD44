#pragma once

#include "../Collider.hpp"
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

class Ship : public Mount, public HardpointOwner, public sf::Drawable, public sf::Transformable, public Collider
{
public:
    Ship();
    ~Ship() = default;

    virtual uint8_t getCollisionMask() const override;
    virtual float getRadius() const override;
    virtual const sf::Transform& getTransform() const override { return sf::Transformable::getTransform(); }
    virtual const sf::Vector2f& getPosition() const override { return sf::Transformable::getPosition(); }
    virtual float getRotation() const override { return sf::Transformable::getRotation(); }

    void update(float aDt) override;
    void draw(sf::RenderTarget& aTarget, sf::RenderStates aStates) const override;

protected:
    virtual void drawShape(sf::RenderTarget& aTarget, sf::RenderStates aStates) const;

private:
    virtual bool onCollision(const Collider* aOther) override;

};

}
