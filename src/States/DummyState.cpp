#include "DummyState.hpp"

#include "../Application.hpp"
#include "../Particles.hpp"

#include "../Game/CogShape.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

using States::DummyState;

Game::CogShape cog(64.f);

void DummyState::handleEvent(const sf::Event& aEvent)
{
    if (aEvent.type != sf::Event::MouseButtonPressed)
        return;

    if (aEvent.mouseButton.button != sf::Mouse::Left)
        return;

    sf::Vector2f mPos(aEvent.mouseButton.x, aEvent.mouseButton.y);
    for (int i = 0; i < 100; ++i)
        getApplication().getParticleManager().emit(Particles::DustPuff(mPos));
}
void DummyState::update(float aDt)
{
}
void DummyState::draw(sf::RenderTarget& aTarget)
{
    cog.setFillColor(sf::Color::Transparent);
    cog.setOutlineColor(sf::Color::White);
    cog.setOutlineThickness(1.f);

    cog.setPosition(aTarget.getView().getCenter());

    aTarget.draw(cog);
}
void DummyState::postDraw(sf::RenderTarget& aTarget)
{
}
void DummyState::preDraw(sf::RenderTarget& aTarget)
{
    aTarget.clear(sf::Color::Black);
}
