#include "DummyState.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

using States::DummyState;

void DummyState::HandleEvent(const sf::Event& aEvent)
{
}
void DummyState::Update(float aDt)
{
}
void DummyState::Draw(sf::RenderTarget& aTarget)
{
    aTarget.clear(sf::Color::White);
}
void DummyState::DrawUi(sf::RenderTarget& aTarget)
{
}
