#include "DummyState.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

using States::DummyState;

void DummyState::handleEvent(const sf::Event& aEvent)
{
}
void DummyState::update(float aDt)
{
}
void DummyState::draw(sf::RenderTarget& aTarget)
{
}
void DummyState::postDraw(sf::RenderTarget& aTarget)
{
}
void DummyState::preDraw(sf::RenderTarget& aTarget)
{
    aTarget.clear(sf::Color::White);
}
