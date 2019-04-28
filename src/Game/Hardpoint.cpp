#include "Hardpoint.hpp"
#include "Attachement.hpp"
#include "../Collider.hpp"
#include "../Util.hpp"

#include <SFML/Graphics/Transformable.hpp>

#include <cmath>

using Game::Attachement;
using Game::Hardpoint;

Hardpoint::Hardpoint()
    : m_attachement(nullptr)
    , m_position()
    , m_direction()
    , m_class(0)
    , m_parent(nullptr)
{
}

Hardpoint::Hardpoint(const Hardpoint& copy)
    : m_attachement(nullptr)
    , m_position(copy.m_position)
    , m_direction(copy.m_direction)
    , m_class(copy.m_class)
    , m_parent(copy.m_parent)
{
}

Hardpoint& Hardpoint::operator=(const Hardpoint& copy)
{
    if (this != &copy)
    {
        m_position = copy.m_position;
        m_direction = copy.m_direction;
    }

    return *this;
}

bool Hardpoint::hasAttachement() const
{
    return !!m_attachement;
}
Attachement& Hardpoint::getAttachement()
{
    return *m_attachement;
}
const Attachement& Hardpoint::getAttachement() const
{
    return *m_attachement;
}
void Hardpoint::setAttachement(Attachement* aAttachement)
{
    if (m_attachement)
        m_attachement->m_hardpoint = nullptr;
    m_attachement.reset(aAttachement);
    m_attachement->m_hardpoint = this;
}
void Hardpoint::setAttachement(std::unique_ptr<Attachement>&& aAttachement)
{
    if (m_attachement)
        m_attachement->m_hardpoint = nullptr;
    m_attachement = std::move(aAttachement);
    m_attachement->m_hardpoint = this;
}
Attachement* Hardpoint::releaseAttachement()
{
    if (m_attachement)
        m_attachement->m_hardpoint = nullptr;
    return m_attachement.release();
}
void Hardpoint::removeAttachment()
{
    m_attachement.reset();
}

uint8_t Hardpoint::getCollisionMask() const
{
    if (m_parent)
        return m_parent->getCollisionMask();
    return CollisionMask_NONE;
}

uint8_t Hardpoint::getTargetCollisionMask() const
{
    if (m_parent)
        return m_parent->getTargetCollisionMask();
    return CollisionMask_NONE;
}

sf::Vector2f Hardpoint::getGlobalPosition() const
{
    if (m_parent)
        return m_parent->getTransform().transformPoint(m_position);
    return m_position;
}
float Hardpoint::getGlobalDirection() const
{
    if (m_parent)
        return m_parent->getRotation() + m_direction;
    return m_direction;
}

void Hardpoint::setParent(const HardpointOwner* aParent)
{
    m_parent = aParent;
}
const Game::HardpointOwner* Hardpoint::getParent() const
{
    return m_parent;
}

const sf::Vector2f& Hardpoint::getPosition() const
{
    return m_position;
}
void Hardpoint::setPosition(const sf::Vector2f& aPos)
{
    m_position = aPos;
}
float Hardpoint::getDirection() const
{
    return m_direction;
}
void Hardpoint::setDirection(float aDir)
{
    m_direction = aDir;
}
int8_t Hardpoint::getClass() const
{
    return m_class;
}
void Hardpoint::setClass(int8_t aClass)
{
    m_class = aClass;
}
