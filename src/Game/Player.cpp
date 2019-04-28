#include "Player.hpp"
#include "CogShape.hpp"
#include "Ship.hpp"
#include "Weapon.hpp"

#include "../Application.hpp"
#include "../Spinor.hpp"
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
    , m_reticule(4.f, 1.5f, 8u)
{
    m_ship = std::make_unique<Ships::Asteroids>();
    m_indicator = CogShape(m_ship->getRadius());

    m_indicator.setOutlineColor(sf::Color(73, 239, 87, 96));
    m_indicator.setOutlineThickness(1.f);
    m_indicator.setOrigin(m_indicator.getRadius(), m_indicator.getRadius());

    m_reticule.setFillColor(sf::Color(190, 15, 15, 96));
    m_reticule.setOutlineColor(sf::Color(220, 0, 0, 128));
    m_reticule.setOutlineThickness(0.5f);
    m_reticule.setOrigin(4.f, 4.f);
}

void Player::update(float aDt)
{
    total += aDt;

    float ang = m_ship->getRotation();
    sf::Vector2f xVec(cos(ang * Deg2Rad()), sin(ang * Deg2Rad()));
    sf::Vector2f yVec(cos((ang + 90) * Deg2Rad()), sin((ang + 90) * Deg2Rad()));

    m_ship->setTargetPosition(Application::getApplication().getRenderWindow().mapPixelToCoords(sf::Mouse::getPosition(Application::getApplication().getRenderWindow())));

    float targetDir = getDirection(m_ship->getPosition(), m_ship->getTargetPosition());
    float curDir = m_ship->getRotation() * Deg2Rad();

    float diff = Spinor::slerpAngle({curDir}, {targetDir}, aDt * 2);
    // TODO: Respect ship max turn speed
    m_ship->setRotation(diff * Rad2Deg());
    // m_ship->rotate(std::min(m_ship->getTurningSpeed(), std::max(-m_ship->getTurningSpeed(), (diff - curDir) * Rad2Deg())));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        m_ship->addImpulse(yVec * m_ship->getAcceleration() * aDt * -m_ship->getSideAccelMult());
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        m_ship->addImpulse(yVec * m_ship->getAcceleration() * aDt * m_ship->getSideAccelMult());

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        m_ship->addImpulse(xVec * m_ship->getAcceleration() * aDt);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        m_ship->addImpulse(xVec * m_ship->getAcceleration() * aDt * -m_ship->getReverseAccelMult());


    m_ship->update(aDt);


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
        m_ship->visitWeapons([](Weapon& w) { w.fire(); });

    m_indicator.setFillColor(sf::Color(22, 140, 32, 96 + std::sin(total * 3) * 18));
    m_indicator.setPosition(m_ship->getPosition());
    m_indicator.setRotation(total * 45.f);

    m_reticule.setPosition(m_ship->getTargetPosition());
    m_reticule.setRotation(total * 125.f);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_indicator, states);
    target.draw(*m_ship, states);
    target.draw(m_reticule, states);
}
