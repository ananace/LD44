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

Player::Player()
    : m_indicator(1.f)
    , m_reticule(8.f)
{
    m_ship = std::make_unique<Ships::Asteroids>();
    m_indicator = CogShape(m_ship->getRadius());
    m_indicator.setFillColor(sf::Color(22, 140, 32, 96 + std::sin(total*4) * 32));
    m_indicator.setOutlineColor(sf::Color(73, 239, 87));
    m_indicator.setOutlineThickness(1.f);
    m_indicator.setOrigin(m_indicator.getRadius(), m_indicator.getRadius());
}

void Player::update(float aDt)
{
    total += aDt;

    m_ship->update(aDt);

    float ang = m_ship->getRotation();
    sf::Vector2f xVec(cos(ang * Deg2Rad()), sin(ang * Deg2Rad()));
    sf::Vector2f yVec(cos((ang + 90) * Deg2Rad()), sin((ang + 90) * Deg2Rad()));

    // TODO: Mouse aiming instead, A/D for strafing
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        m_ship->rotate(-aDt * m_ship->getTurningSpeed());
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        m_ship->rotate(aDt * m_ship->getTurningSpeed());

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        m_ship->addImpulse(xVec * m_ship->getAcceleration() * aDt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        m_ship->visitWeapons([](Weapon& w) { w.fire(); });

    m_indicator.setPosition(m_ship->getPosition());
    m_indicator.setRotation(total * 45.f);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_indicator, states);
    target.draw(*m_ship, states);
}
