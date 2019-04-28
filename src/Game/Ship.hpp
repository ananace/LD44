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
    ~Ship();

    void finalize();

    uint8_t getCollisionMask() const override;
    uint8_t getTargetCollisionMask() const override;
    void setCollisionMask(uint8_t);
    void setTargetCollisionMask(uint8_t);
    virtual float getRadius() const override;
    virtual float getAcceleration() const;
    virtual float getSideAccelMult() const;
    virtual float getReverseAccelMult() const;
    virtual float getTurningSpeed() const;
    virtual float getMaxSpeed() const;

    float getHealth() const;

    const sf::Transform& getTransform() const override { return sf::Transformable::getTransform(); }
    const sf::Vector2f& getPosition() const override { return sf::Transformable::getPosition(); }
    const sf::Vector2f& getVelocity() const;
    const sf::Vector2f& getTargetPosition() const override;
    float getRotation() const override { return sf::Transformable::getRotation(); }

    void setTargetPosition(const sf::Vector2f& aTarget);
    void setVelocity(const sf::Vector2f& aVelocity);
    void setVelocity(float aVelocity);
    void addImpulse(const sf::Vector2f& aForce);
    void addImpulse(float aForce);

    void update(float aDt) override;
    void draw(sf::RenderTarget& aTarget, sf::RenderStates aStates) const override;

protected:
    virtual void drawShape(sf::RenderTarget& aTarget, sf::RenderStates aStates) const = 0;

private:
    virtual bool onCollision(const Collider* aOther) override;

    uint8_t m_collMask, m_targetCollMask;
    sf::Vector2f m_velocity,
                 m_target;
    float m_health;
};

}
