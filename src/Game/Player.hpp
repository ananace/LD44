#pragma once

#include "Attachement.hpp"
#include "CogShape.hpp"
#include "Ship.hpp"

#include <SFML/Graphics/Drawable.hpp>

namespace Game
{

class Player : public sf::Drawable
{
public:
    Player();

    void update(float aDt);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    Ship& getShip();
    const Ship& getShip() const;

private:
    std::unique_ptr<Ship> m_ship;
    CogShape m_indicator,
             m_reticule;
};

}
