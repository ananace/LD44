#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <deque>

namespace sf { class RenderTarget; }

class ParticleManager
{
public:
    struct Particle
    {
        bool Above;
        float Lifetime, Angle, RotVel, Friction;
        sf::IntRect TexCoords;
        sf::Vector2f Velocity;
        sf::Vertex Vertex;
    };

    void update(float aDt);

    void drawAbove(sf::RenderTarget& aTarget);
    void drawBelow(sf::RenderTarget& aTarget);

private:
    sf::Texture m_particleSheet;
    std::deque<Particle> m_particles;
};
