#include "Ship.hpp"
#include "Hardpoint.hpp"
#include "Weapon.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

using Game::Ship;

Ship::Ship()
{
    Hardpoint hp;
    hp.setPosition({ 20.0f, 0.0f });
    hp.setDirection(0.f);

    addHardpoint(hp);
}

float Ship::getRadius() const
{
    return 16.f;
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

    sf::CircleShape cs(4.f, 16);
    cs.setOrigin(4.f, 4.f);
    cs.setFillColor(sf::Color::Black);
    cs.setOutlineColor(sf::Color(128,128,128));
    cs.setOutlineThickness(0.75f);

    visitHardpoints([&](const Hardpoint& hp) {
        cs.setPosition(hp.getPosition());

        aTarget.draw(cs, aStates);
    });
}
