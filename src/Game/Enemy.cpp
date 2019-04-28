#include "Enemy.hpp"

#include "../Util.hpp"

#include "Ships/Asteroids.hpp"

using Game::Enemy;
using Game::Ship;

Enemy::Enemy(uint8_t aDifficulty)
    : m_flags(EnemyFlags_NONE)
    , m_difficulty(aDifficulty)
    , m_state(EnemyState_Idle)
{
    m_ship = std::make_unique<Ships::Asteroids>();
}

bool Enemy::hasFlag(uint8_t aFlag) const
{
    return (m_flags & aFlag) != 0;
}
void Enemy::setFlag(uint8_t aFlag, bool aState)
{
    if (aState)
        m_flags |= aFlag;
    else
        m_flags &= ~aFlag;
}

Game::EnemyState Enemy::getState() const
{
    return m_state;
}
void Enemy::setState(EnemyState aState)
{
    m_state = aState;
}

void Enemy::setTarget(const Ship* aTarget)
{
    m_targetShip = aTarget;
}
const Ship* Enemy::getTarget() const
{
    return m_targetShip;
}

Ship& Enemy::getShip()
{
    return *m_ship;
}
const Ship& Enemy::getShip() const
{
    return *m_ship;
}

void Enemy::update(float aDt)
{
    sf::Vector2f targetPosition;

    if (m_state == EnemyState_Attacking || m_state == EnemyState_Escorting)
    {
        if (!m_targetShip)
            m_state = EnemyState_Roaming;
        else
        {
            sf::Vector2f target = m_targetShip->getPosition();
            if (m_state == EnemyState_Escorting)
                target -= sf::Vector2f(cos(m_targetShip->getRotation() * Deg2Rad() + (Pi() / 2) * hasFlag(EnemyFlags_Offset) ? 1 : -1), sin(m_targetShip->getRotation() * Deg2Rad() + (Pi() / 2) * hasFlag(EnemyFlags_Offset) ? 1 : -1)) * m_targetShip->getRadius() * 1.f;
            else
            {
                float direction = getDirection(m_ship->getPosition(), target);
                target -= sf::Vector2f(cos(direction), sin(direction)) * m_targetShip->getRadius() * 4.f;
            }

            float targetDist = getVectorLength(target - m_ship->getPosition());
            float targetDir = getDirection(m_ship->getPosition(), target);

            // m_ship->setPosition(target);
            m_ship->setRotation(targetDir * Rad2Deg());
            m_ship->setVelocity(std::min(targetDist - (m_targetShip->getRadius() * 4.f), m_ship->getMaxSpeed() * 0.75f));
        }
    }

    m_ship->update(aDt);
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    m_ship->draw(target, states);
}
