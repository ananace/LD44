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

    void finalize();

    uint8_t getCollisionMask() const override;
    virtual float getRadius() const override;
    virtual float getAcceleration() const;
    virtual float getSideAccelMult() const;
    virtual float getReverseAccelMult() const;
    virtual float getTurningSpeed() const;
    virtual float getMaxSpeed() const;

    const sf::Transform& getTransform() const override { return sf::Transformable::getTransform(); }
    const sf::Vector2f& getPosition() const override { return sf::Transformable::getPosition(); }
    const sf::Vector2f& getVelocity() const;
    const sf::Vector2f& getTargetPosition() const override;
    float getRotation() const override { return sf::Transformable::getRotation(); }

    void setTargetPosition(const sf::Vector2f& aTarget);
    void addImpulse(const sf::Vector2f& aForce);

    void update(float aDt) override;
    void draw(sf::RenderTarget& aTarget, sf::RenderStates aStates) const override;

protected:
    virtual void drawShape(sf::RenderTarget& aTarget, sf::RenderStates aStates) const = 0;

private:
    virtual bool onCollision(const Collider* aOther) override;

    sf::Vector2f m_velocity,
                 m_target;
};

}
