#include "Application.hpp"
#include "States/DummyState.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <chrono>

typedef std::chrono::high_resolution_clock chrono_clock;
typedef chrono_clock::duration duration;
typedef chrono_clock::time_point time_point;
typedef std::chrono::duration<float> dt_seconds;

Application* Application::s_singleton = nullptr;

Application::Application()
{
    if (s_singleton)
        throw std::runtime_error("Multiple Application instances");
    s_singleton = this;

    setCurState(new States::DummyState());
}

Application::~Application()
{
    if (s_singleton == this)
        s_singleton = nullptr;
}

Application& Application::getApplication()
{
    return *s_singleton;
}

sf::Font& Application::getDefaultFont() const
{
    static sf::Font s_defaultFont;

    std::string fonts[] = {
#ifdef SFML_SYSTEM_LINUX
        "/usr/share/fonts/corefonts/andalemo.ttf",
        "/usr/share/fonts/dejavu/DejaVuSansMono.ttf",
        "/usr/share/fonts/liberation-fonts/LiberationMono-Regular.ttf"
#elif SFML_SYSTEM_WINDOWS
        "C:\\Windows\\Fonts\\AndaleMono.ttf",
#endif
    };

    if (s_defaultFont.getInfo().family.empty())
        for (auto& path : fonts)
            if (s_defaultFont.loadFromFile(path))
                break;

    return s_defaultFont;
}

IState& Application::getCurState()
{
    return *m_curState;
}
const IState& Application::getCurState() const
{
    return *m_curState;
}
void Application::setCurState(IState* aState)
{
    aState->m_app = this;
    m_curState.reset(aState);
}

CollisionManager& Application::getCollisionManager()
{
    return m_collision;
}
ParticleManager& Application::getParticleManager()
{
    return m_particles;
}
ProjectileManager& Application::getProjectileManager()
{
    return m_projectiles;
}
sf::RenderWindow& Application::getRenderWindow()
{
    return m_window;
}

void Application::run()
{
    time_point start = chrono_clock::now(),
               end = chrono_clock::now(),
               lastFPS = chrono_clock::now();
    duration dt;
    sf::Event ev;

    int realFPS = 0, frames = 0;

    m_window.create(sf::VideoMode(800, 600), "LD44", sf::Style::Default, sf::ContextSettings(0, 0, 2));
    m_window.setFramerateLimit(150);
    m_uiView = m_window.getDefaultView();

    while (m_window.isOpen())
    {
        dt = end - start;
        start = chrono_clock::now();
        ++frames;

        if (start - lastFPS > std::chrono::seconds(1))
        {
            lastFPS = start;
            realFPS = frames;
            frames = 0;
        }

        while (m_window.pollEvent(ev))
        {
            m_curState->handleEvent(ev);

            switch (ev.type)
            {
            case sf::Event::Closed:
                m_window.close(); break;
            case sf::Event::Resized:
                m_uiView.setSize(sf::Vector2f(m_window.getSize()));
                m_uiView.setCenter(m_uiView.getSize() / 2.f);
                break;

            default: break;
            }
        }

        float f_dt = std::chrono::duration_cast<dt_seconds>(dt).count();
        m_projectiles.update(f_dt);
        m_collision.update(f_dt);
        m_curState->update(f_dt);
        m_particles.update(f_dt);

        m_curState->preDraw(m_window);

        m_particles.drawBelow(m_window);

        m_curState->draw(m_window);

        m_projectiles.draw(m_window);

        m_particles.drawAbove(m_window);

        m_window.setView(m_uiView);

        m_curState->postDraw(m_window);

        char fpsCount[32];
        snprintf(fpsCount, 32, "FPS: %d", realFPS);
        sf::Text stats(fpsCount, getDefaultFont(), 12u);
        stats.setFillColor(sf::Color::White);
        stats.setOutlineColor(sf::Color::Black);
        stats.setOutlineThickness(1.5f);
        stats.move(5, 2);
        m_window.draw(stats);

        m_window.display();

        end = chrono_clock::now();
    }
}
