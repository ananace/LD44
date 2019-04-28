#pragma once

#include "../IState.hpp"
#include "../Game/Player.hpp"

namespace States
{

class DummyState : public IState
{
public:
    void handleEvent(const sf::Event& aEvent) override;
    void update(float aDt) override;
    void preDraw(sf::RenderTarget& aTarget) override;
    void draw(sf::RenderTarget& aTarget) override;
    void postDraw(sf::RenderTarget& aTarget) override;

private:
    Game::Player m_player;
};

}
