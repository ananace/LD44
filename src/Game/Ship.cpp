#include "Ship.hpp"
#include "Hardpoint.hpp"
#include "Weapon.hpp"

#include "../Application.hpp"
#include "../Util.hpp"
#include "Weapons/Gun.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

using Game::Ship;

Ship::Ship()
    : m_collMask(CollisionMask_ALL)
    , m_targetCollMask(CollisionMask_NONE)
    , m_health(3)
{
    Application::getApplication().getCollisionManager().addCollider(this);
}

Ship::~Ship()
{
    Application::getApplication().getCollisionManager().removeCollider(this);
}

void Ship::finalize()
{
    visitHardpoints([this](Hardpoint& hardpoint) { hardpoint.setParent(this); });
}

uint8_t Ship::getCollisionMask() const
{
    return m_collMask;
}
uint8_t Ship::getTargetCollisionMask() const
{
    return m_targetCollMask;
}
void Ship::setCollisionMask(uint8_t aCollMask)
{
    m_collMask = aCollMask;
}
void Ship::setTargetCollisionMask(uint8_t aCollMask)
{
    m_targetCollMask = aCollMask;
}
float Ship::getRadius() const
{
    return 16.f;
}
float Ship::getAcceleration() const
{
    return 50.f;
}
float Ship::getSideAccelMult() const
{
    return 0.75f;
}
float Ship::getReverseAccelMult() const
{
    return 0.5f;
}
float Ship::getTurningSpeed() const
{
    return 110.f;
}
float Ship::getMaxSpeed() const
{
    return 250.f;
}
float Ship::getHealth() const
{
    return m_health;
}

const sf::Vector2f& Ship::getVelocity() const
{
    return m_velocity;
}
const sf::Vector2f& Ship::getTargetPosition() const
{
    return m_target;
}
void Ship::setTargetPosition(const sf::Vector2f& aTarget)
{
    m_target = aTarget;
}
void Ship::setVelocity(const sf::Vector2f& aVelocity)
{
    m_velocity = aVelocity;
}
void Ship::setVelocity(float aVelocity)
{
    m_velocity = sf::Vector2f(cos(getRotation() * Deg2Rad()), sin(getRotation() * Deg2Rad())) * aVelocity;
}
void Ship::addImpulse(const sf::Vector2f& aForce)
{
    m_velocity += aForce;
}
void Ship::addImpulse(float aForce)
{
    m_velocity += sf::Vector2f(cos(getRotation() * Deg2Rad()), sin(getRotation() * Deg2Rad())) * aForce;
}

void Ship::update(float aDt)
{
    if (getVectorLength(m_velocity) > getMaxSpeed())
        m_velocity = setVectorLength(m_velocity, getMaxSpeed());
    setPosition(getPosition() + m_velocity * aDt);

    visitHardpoints([aDt](Hardpoint& hp) {
        if (!hp.hasAttachement())
            return;

        hp.getAttachement().update(aDt);
    });
}

bool Ship::onCollision(const Collider* aOther)
{
    printf("Ship[%p]: Collision\n", this);

    m_health -= 1.f;

    return false;
}

void Ship::draw(sf::RenderTarget& aTarget, sf::RenderStates aStates) const
{
    aStates.transform *= getTransform();

    drawShape(aTarget, aStates);

    // Debug hardcode rendering;

    sf::CircleShape cs(2.f, 16);
    cs.setOrigin(2.f, 2.f);
    cs.setFillColor(sf::Color::Transparent);
    cs.setOutlineColor(sf::Color(128,128,128,128));
    cs.setOutlineThickness(0.75f);

    sf::VertexArray arr(sf::LineStrip, 5);
    arr[0] = { { -5, 0 }, sf::Color(255,255,255,96) };
    arr[1] = { { 5, 0 }, sf::Color(255,255,255,96) };
    arr[2] = { { 2, -2 }, sf::Color(255,255,255,96) };
    arr[3] = { { 5, 0 }, sf::Color(255,255,255,96) };
    arr[4] = { { 2, 2 }, sf::Color(255,255,255,96) };

    visitHardpoints([&](const Hardpoint& hp) {
        uint8_t visualClass = abs(hp.getClass());
        if (visualClass == 0)
            visualClass = 1;
        aStates.transform.translate(hp.getPosition());
        aStates.transform.rotate(hp.getDirection());
        aStates.transform.scale(visualClass, visualClass);

        aTarget.draw(cs, aStates);
        if (hp.getClass() > 0)
            aTarget.draw(arr, aStates);

        aStates.transform.scale(1.f / visualClass, 1.f / visualClass);
        aStates.transform.rotate(-hp.getDirection());
        aStates.transform.translate(-hp.getPosition());
    });
}
