#pragma once

#include "../IState.hpp"

namespace States
{

class DummyState : public IState
{
    void handleEvent(const sf::Event& aEvent) override;
    void update(float aDt) override;
    void draw(sf::RenderTarget& aTarget) override;
    void drawUi(sf::RenderTarget& aTarget) override;
};

}
