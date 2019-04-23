#include "ParticleManager.hpp"

void ParticleManager::update(float aDt)
{
    for (auto& particle : m_particles)
    {
        particle.Lifetime -= aDt;
    }
}

void ParticleManager::drawAbove(sf::RenderTarget& aTarget)
{
}
void ParticleManager::drawBelow(sf::RenderTarget& aTarget)
{
}
