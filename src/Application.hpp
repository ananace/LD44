#pragma once

#include "IState.hpp"
#include "ParticleManager.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>

class Application
{
public:
    Application();
    Application(const Application&) = delete;
    ~Application();

    Application& operator=(const Application&) = delete;

    static Application& getApplication();

    sf::Font& getDefaultFont() const;

    IState& getCurState();
    const IState& getCurState() const;
    void setCurState(IState* aState);

    ParticleManager& getParticleManager();

    void run();

private:
    static Application* s_singleton;

    std::unique_ptr<IState> m_curState;
    ParticleManager m_particles;
    sf::RenderWindow m_window;
    sf::View m_uiView;
};
