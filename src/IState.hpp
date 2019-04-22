#pragma once

namespace sf { class RenderTarget; class Event; }

class IState
{
public:
    virtual void HandleEvent(const sf::Event& aEvent) = 0;
    virtual void Update(float aDt) = 0;
    virtual void Draw(sf::RenderTarget& aTarget) = 0;
    virtual void DrawUi(sf::RenderTarget& aTarget) = 0;
};
