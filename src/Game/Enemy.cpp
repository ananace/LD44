#include "Enemy.hpp"

using Game::Enemy;

Enemy::Enemy(uint8_t aDifficulty)
    : m_flags(EnemyFlags_NONE)
    , m_difficulty(aDifficulty)
    , m_state(EnemyState_Idle)
{
}

bool Enemy::hasFlag(uint8_t aFlag) const
{
    return (m_flags & aFlag) == aFlag;
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

void Enemy::update(float aDt)
{
    sf::Vector2f targetPosition;

    if (m_state == EnemyState_Attacking)
    {
        if (!m_targetShip)
            m_state = EnemyState_Roaming;
        else
        {

        }
    }

    m_ship->update(aDt);
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    m_ship->draw(target, states);
}
