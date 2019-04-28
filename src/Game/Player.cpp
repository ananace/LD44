#include "Player.hpp"
#include "CogShape.hpp"
#include "Ship.hpp"
#include "Weapon.hpp"

#include "../Util.hpp"
#include "Ships/Asteroids.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <cmath>

using Game::CogShape;
using Game::Player;
using Game::Ship;

float total = 0;
CogShape cog(14.f);
std::unique_ptr<Ship> ship;

Player::Player()
{
    ship = std::make_unique<Ships::Asteroids>();
    cog = CogShape(ship->getRadius());
    cog.setFillColor(sf::Color(22, 140, 32, 96 + std::sin(total*4) * 32));
    cog.setOutlineColor(sf::Color(73, 239, 87));
    cog.setOutlineThickness(1.f);
    cog.setOrigin(cog.getRadius(), cog.getRadius());
}

void Player::update(float aDt)
{
    total += aDt;

    ship->update(aDt);

    float ang = ship->getRotation();
    sf::Vector2f xVec(cos(ang * Deg2Rad()), sin(ang * Deg2Rad()));
    sf::Vector2f yVec(cos((ang + 90) * Deg2Rad()), sin((ang + 90) * Deg2Rad()));

    // TODO: Mouse aiming instead, A/D for strafing
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        ship->rotate(-aDt * ship->getTurningSpeed());
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        ship->rotate(aDt * ship->getTurningSpeed());

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        ship->addImpulse(xVec * ship->getAcceleration() * aDt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        ship->visitWeapons([](Weapon& w) { w.fire(); });
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    cog.setPosition(ship->getPosition());
    cog.setRotation(total * 45.f);

    target.draw(cog, states);
    target.draw(*ship, states);
}
