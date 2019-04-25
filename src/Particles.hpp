#pragma once

#include "ParticleManager.hpp"
#include "Util.hpp"

#include <random>

namespace Particles
{

inline ParticleManager::Particle DustPuff(const sf::Vector2f& aPos = {}) {
    static std::random_device dev;
    static std::uniform_real_distribution<float> rotVel(-Pi() / 4.f, Pi() / 4.f);
    static std::uniform_real_distribution<float> ang(0, Pi() * 2.f);
    static std::uniform_real_distribution<float> vel(1.f, 15.f);

    float angle = ang(dev);
    float velocity = vel(dev);

    return {
        true,
        1.5f + vel(dev) / 2.f, angle, rotVel(dev), 0.5f,
        {0, 0, 16, 16},
        {std::sin(angle) * velocity, std::cos(angle) * velocity},
        {aPos, sf::Color::White},
    };
};

}
