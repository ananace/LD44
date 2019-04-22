#pragma once

#include "../IState.hpp"

namespace States
{

class DummyState : public IState
{
    void HandleEvent(const sf::Event& aEvent) override;
    void Update(float aDt) override;
    void Draw(sf::RenderTarget& aTarget) override;
    void DrawUi(sf::RenderTarget& aTarget) override;
};

}
