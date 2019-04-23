#pragma once

#include "../IState.hpp"

namespace Game
{

class GameState : public IState
{
    void handleEvent(const sf::Event& aEvent) override;
    void update(float aDt) override;
    void draw(sf::RenderTarget& aTarget) override;
    void drawUi(sf::RenderTarget& aTarget) override;
};

}
