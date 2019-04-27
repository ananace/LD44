#include "Player.hpp"
#include "CogShape.hpp"
#include "Ship.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <cmath>

using Game::CogShape;
using Game::Player;
using Game::Ship;

float total = 0;
CogShape cog(14.f);
Ship ship;

void Player::update(float aDt)
{
    total += aDt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        ship.rotate(-aDt * 30.f);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        ship.rotate(aDt * 30.f);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    cog.setFillColor(sf::Color(22, 140, 32, 96 + std::sin(total*4) * 32));
    cog.setOutlineColor(sf::Color(73, 239, 87));
    cog.setOutlineThickness(1.f);

    cog.setOrigin(14.f, 14.f);
    ship.setPosition(target.getView().getCenter());

    cog.setPosition(ship.getPosition());
    cog.rotate(0.05f);

    target.draw(cog, states);
    target.draw(ship, states);
}
