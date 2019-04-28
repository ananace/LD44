#include "Asteroids.hpp"

#include "../Weapons/Gun.hpp"
#include "../Weapons/MissileLauncher.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

using Game::Ships::Asteroids;

Asteroids::Asteroids()
    : m_shipShape(4)
    , m_centerCog(8.f)
    , m_frontCog(4.f, 1.25f, 5u, 1, false)
{
    m_shipShape.setPoint(0, { 40, 0 });
    m_shipShape.setPoint(1, { -20, 20 });
    m_shipShape.setPoint(2, { -10, 0 });
    m_shipShape.setPoint(3, { -20, -20 });

    m_shipShape.setFillColor(sf::Color::Black);
    m_shipShape.setOutlineColor(sf::Color::White);
    m_shipShape.setOutlineThickness(1.5f);

    Hardpoint hp;
    hp.setPosition({ 20.0f, 0.0f });
    hp.setDirection(0.f);
    hp.setClass(2);
    addHardpoint(hp);

    hp.setPosition({ -16.0f, -16.0f });
    hp.setDirection(-45.f);
    hp.setClass(1);
    addHardpoint(hp);

    hp.setPosition({ -16.0f, 16.0f });
    hp.setDirection(45.f);
    addHardpoint(hp);

    hp.setPosition({ 0.0f, 0.0f });
    hp.setDirection(0.f);
    hp.setClass(-1);
    addHardpoint(hp);

    getHardpoint(0).setAttachement(new Game::Weapons::Gun());
    getHardpoint(1).setAttachement(new Game::Weapons::MissileLauncher());
    getHardpoint(2).setAttachement(new Game::Weapons::MissileLauncher());

    m_centerCog.setOrigin(8.f, 8.f);
    m_centerCog.setFillColor(sf::Color::Transparent);
    m_centerCog.setOutlineColor(sf::Color::White);
    m_centerCog.setOutlineThickness(1.f);
    m_frontCog.rotate(-15.f);
    m_frontCog.setPosition(16.f, 0.f);
    m_frontCog.setOrigin(4.f, 4.f);
    m_frontCog.setFillColor(sf::Color::Transparent);
    m_frontCog.setOutlineColor(sf::Color::White);
    m_frontCog.setOutlineThickness(1.f);

    finalize();
}

float Asteroids::getRadius() const
{
    return 32.f;
}

void Asteroids::update(float aDt)
{
    m_centerCog.rotate(aDt * 48.f);
    m_frontCog.rotate(aDt * -96.f);
    Ship::update(aDt);
}

void Asteroids::drawShape(sf::RenderTarget& aTarget, sf::RenderStates aStates) const
{
    aTarget.draw(m_shipShape, aStates);
    aTarget.draw(m_centerCog, aStates);
    aTarget.draw(m_frontCog, aStates);
}
