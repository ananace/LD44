#include "DummyState.hpp"

#include "../Application.hpp"
#include "../Particles.hpp"

#include "../Game/Player.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

using States::DummyState;

Game::Player player;

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
    player.update(aDt);
}
void DummyState::draw(sf::RenderTarget& aTarget)
{
    aTarget.draw(player);
}
void DummyState::postDraw(sf::RenderTarget& aTarget)
{
}
void DummyState::preDraw(sf::RenderTarget& aTarget)
{
    aTarget.clear(sf::Color::Black);
}
