#pragma once

namespace sf { class RenderTarget; class Event; }
class Application;

class IState
{
public:
    virtual void handleEvent(const sf::Event& aEvent) = 0;
    virtual void update(float aDt) = 0;
    virtual void preDraw(sf::RenderTarget& aTarget) = 0;
    virtual void draw(sf::RenderTarget& aTarget) = 0;
    virtual void postDraw(sf::RenderTarget& aTarget) = 0;

protected:
    Application& getApplication() const { return *m_app; }

private:
    friend class Application;
    Application* m_app;
};
