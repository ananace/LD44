#pragma once

#include <SFML/System/Vector2.hpp>

#include <cmath>

constexpr float Pi() { return std::atan(1) * 4; }
constexpr float Deg2Rad() { return Pi() / 180.f; }
constexpr float Rad2Deg() { return 180.f / Pi(); }

float getVectorLength(const sf::Vector2f& aVec);
sf::Vector2f setVectorLength(const sf::Vector2f& aVec, float aLength);
sf::Vector2f operator*(const sf::Vector2f& aLhs, const sf::Vector2f& aRhs);
