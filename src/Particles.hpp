#pragma once

#include "ParticleManager.hpp"
#include "Util.hpp"

#include <random>

namespace Particles
{

inline ParticleManager::Particle Smoke(const sf::Vector2f& aPos = {}) {
    static std::random_device dev;
    static std::uniform_real_distribution<float> rotVel(-Pi() / 4.f, Pi() / 4.f);
    static std::uniform_real_distribution<float> ang(0, Pi() * 2.f);
    static std::uniform_real_distribution<float> vel(0.1f, 1.5f);

    float angle = ang(dev);
    float velocity = vel(dev);

    return {
        false,
        1.5f + vel(dev) / 2.f, angle, rotVel(dev), 0.15f,
        {0, 0, 16, 16},
        {std::sin(angle) * velocity, std::cos(angle) * velocity},
        {aPos, { 128, 128, 128 }},
    };
};

}
