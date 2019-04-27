#include "Hardpoint.hpp"
#include "Attachement.hpp"

using Game::Attachement;
using Game::Hardpoint;

Hardpoint::Hardpoint(const Hardpoint& copy)
    : m_position(copy.m_position)
    , m_direction(copy.m_direction)
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
    m_attachement.reset(aAttachement);
}
void Hardpoint::setAttachement(std::unique_ptr<Attachement>&& aAttachement)
{
    m_attachement = std::move(aAttachement);
}
void Hardpoint::removeAttachment()
{
    m_attachement.reset();
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
