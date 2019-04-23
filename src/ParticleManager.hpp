#pragma once

#include <SFML/Graphics/Vertex.hpp>
#include <deque>

namespace sf { class RenderTarget; }

class ParticleManager
{
public:
    void update(float aDt);

    void drawAbove(sf::RenderTarget& aTarget);
    void drawBelow(sf::RenderTarget& aTarget);

private:
    struct Particle
    {
        float Lifetime;
    };

    std::deque<Particle> m_particles;
};
