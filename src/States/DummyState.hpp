#pragma once

#include "../IState.hpp"

namespace States
{

class DummyState : public IState
{
    void handleEvent(const sf::Event& aEvent) override;
    void update(float aDt) override;
    void preDraw(sf::RenderTarget& aTarget) override;
    void draw(sf::RenderTarget& aTarget) override;
    void postDraw(sf::RenderTarget& aTarget) override;
};

}
