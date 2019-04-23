#pragma once

#include <SFML/System/Vector2.hpp>

#include <cmath>

constexpr float Pi() { return std::atan(1) * 4; }
constexpr float Deg2Rad() { return Pi() / 180.f; }
constexpr float Rad2Deg() { return 180.f / Pi(); }

sf::Vector2f operator*(const sf::Vector2f& aLhs, const sf::Vector2f& aRhs)
{
    return { aLhs.x * aRhs.x, aLhs.y * aRhs.y };
}
