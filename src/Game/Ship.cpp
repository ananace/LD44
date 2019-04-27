#include "Ship.hpp"
#include "Hardpoint.hpp"
#include "Weapon.hpp"

#include "Weapons/Gun.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

using Game::Ship;

Ship::Ship()
{
    Hardpoint hp;
    hp.setPosition({ 10.0f, 0.0f });
    hp.setDirection(0.f);
    addHardpoint(hp);

    getHardpoint(0).setAttachement(new Game::Weapons::Gun());

    hp.setPosition({ -8.0f, -8.0f });
    hp.setDirection(-45.f);
    addHardpoint(hp);

    hp.setPosition({ -8.0f, 8.0f });
    hp.setDirection(45.f);
    addHardpoint(hp);
}

float Ship::getRadius() const
{
    return 16.f;
}

void Ship::update(float aDt)
{
    visitHardpoints([aDt](Hardpoint& hp) {
        if (!hp.hasAttachement())
            return;

        hp.getAttachement().update(aDt);
    });
}

void Ship::draw(sf::RenderTarget& aTarget, sf::RenderStates aStates) const
{
    aStates.transform *= getTransform();

    drawShape(aTarget, aStates);
}

void Ship::drawShape(sf::RenderTarget& aTarget, sf::RenderStates aStates) const
{
    sf::ConvexShape shape(4);
    shape.setPoint(0, { 0, -20 });
    shape.setPoint(1, { 10, 10 });
    shape.setPoint(2, { 0, 5 });
    shape.setPoint(3, { -10, 10 });

    shape.setFillColor(sf::Color::Black);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(1.5f);

    shape.rotate(90.f);

    aTarget.draw(shape, aStates);

    // Debug hardcode rendering;

    sf::CircleShape cs(5.f, 16);
    cs.setOrigin(5.f, 5.f);
    cs.setFillColor(sf::Color::Black);
    cs.setOutlineColor(sf::Color(128,128,128));
    cs.setOutlineThickness(0.75f);

    sf::VertexArray arr(sf::LineStrip, 5);
    arr[0] = { { -5, 0 }, sf::Color::White };
    arr[1] = { { 5, 0 }, sf::Color::White };
    arr[2] = { { 2, -2 }, sf::Color::White };
    arr[3] = { { 5, 0 }, sf::Color::White };
    arr[4] = { { 2, 2 }, sf::Color::White };

    visitHardpoints([&](const Hardpoint& hp) {
        aStates.transform.translate(hp.getPosition());
        aStates.transform.rotate(hp.getDirection());

        aTarget.draw(cs, aStates);
        aTarget.draw(arr, aStates);

        aStates.transform.rotate(-hp.getDirection());
        aStates.transform.translate(-hp.getPosition());
    });
}
