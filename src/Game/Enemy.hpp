#pragma once

#include "Ship.hpp"

#include <SFML/Graphics/Drawable.hpp>

namespace Game
{

enum EnemyFlags : uint8_t
{
    EnemyFlags_Aggressive = 1 << 0,

    EnemyFlags_Offset = 1 << 1,

    EnemyFlags_NONE = 0,
    EnemyFlags_ALL = 0xFF
};

enum EnemyState : uint8_t
{
    EnemyState_Idle = 0,
    EnemyState_Escorting,
    EnemyState_Attacking,
    EnemyState_Roaming
};

class Enemy : public sf::Drawable
{
public:
    Enemy(uint8_t aDifficulty);

    bool isDead() const;

    bool hasFlag(uint8_t aFlag) const;
    void setFlag(uint8_t aFlag, bool aState = true);

    EnemyState getState() const;
    void setState(EnemyState aState);

    void setTarget(const Ship* aTarget);
    const Ship* getTarget() const;

    Ship& getShip();
    const Ship& getShip() const;

    void update(float aDt);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    std::unique_ptr<Ship> m_ship;

    const Ship* m_targetShip;

    uint8_t m_flags,
            m_difficulty;
    EnemyState m_state;
};

}

