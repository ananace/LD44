#include "ParticleManager.hpp"
#include "Util.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <algorithm>
#include <cmath>

inline void _setupQuad(const ParticleManager::Particle& particle, sf::Vertex quad[5], sf::Vector2f axises[2], sf::Vector2f& size)
{
    axises[0] = sf::Vector2f(std::cos(particle.Angle), std::sin(particle.Angle));
    axises[1] = sf::Vector2f(std::cos(particle.Angle + Pi()/2.f), std::sin(particle.Angle + Pi()/2.f));
    size.x = particle.TexCoords.width;
    size.y = particle.TexCoords.height;

    quad[0].color = particle.Vertex.color;
    quad[0].position = particle.Vertex.position + (size.x * -0.5f * axises[0]) + (size.y * -0.5f * axises[1]);
    quad[0].texCoords = sf::Vector2f(particle.TexCoords.left, particle.TexCoords.top);
    quad[1].color = particle.Vertex.color;
    quad[1].position = particle.Vertex.position + (size.x * 0.5f * axises[0]) + (size.y * -0.5f * axises[1]);
    quad[1].texCoords = sf::Vector2f(particle.TexCoords.left + particle.TexCoords.width, particle.TexCoords.top);
    quad[2].color = particle.Vertex.color;
    quad[2].position = particle.Vertex.position + (size.x * 0.5f * axises[0]) + (size.y * 0.5f * axises[1]);
    quad[2].texCoords = sf::Vector2f(particle.TexCoords.left + particle.TexCoords.width, particle.TexCoords.top + particle.TexCoords.height);
    quad[3].color = particle.Vertex.color;
    quad[3].position = particle.Vertex.position + (size.x * -0.5f * axises[0]) + (size.y * 0.5f * axises[1]);
    quad[3].texCoords = sf::Vector2f(particle.TexCoords.left, particle.TexCoords.top + particle.TexCoords.height);
    quad[4].color = particle.Vertex.color;
    quad[4].position = particle.Vertex.position + (size.x * -0.5f * axises[0]) + (size.y * -0.5f * axises[1]);
    quad[4].texCoords = sf::Vector2f(particle.TexCoords.left, particle.TexCoords.top);
}

ParticleManager::ParticleManager()
{
    // TODO: Load spritesheet
}

ParticleManager::Particle& ParticleManager::emit(const Particle& aTemplate)
{
    m_particles.emplace_back(aTemplate);
    return m_particles.back();
}

void ParticleManager::update(float aDt)
{
    for (auto& particle : m_particles)
    {
        particle.Lifetime -= aDt;
        particle.Vertex.position += particle.Velocity * aDt;
        particle.Velocity -= particle.Velocity * particle.Friction * aDt;
        particle.Angle += particle.RotVel * aDt;
    }

    auto ebegin = std::remove_if(m_particles.begin(), m_particles.end(), [](const auto& p) { return p.Lifetime <= 0; });
    m_particles.erase(ebegin, m_particles.end());
}

void ParticleManager::drawAbove(sf::RenderTarget& aTarget)
{
    sf::RenderStates states;
    states.texture = &m_particleSheet;

    sf::Vector2f axises[2];
    sf::Vector2f size;
    sf::Vertex quad[5];

    for (auto& particle : m_particles)
    {
        if (!particle.Above)
            continue;

        _setupQuad(particle, quad, axises, size);
        aTarget.draw(quad, 5, sf::TriangleStrip, states);
    }
}
void ParticleManager::drawBelow(sf::RenderTarget& aTarget)
{
    sf::RenderStates states;
    states.texture = &m_particleSheet;

    sf::Vector2f axises[2];
    sf::Vector2f size;
    sf::Vertex quad[5];

    for (auto& particle : m_particles)
    {
        if (particle.Above)
            continue;

        _setupQuad(particle, quad, axises, size);
        aTarget.draw(quad, 5, sf::TriangleStrip, states);
    }
}
