#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <cmath>

#ifdef _WIN32
constexpr float Pi() { return 3.14159f; }
#else
constexpr float Pi() { return std::atan(1) * 4; }
#endif
constexpr float Deg2Rad() { return Pi() / 180.f; }
constexpr float Rad2Deg() { return 180.f / Pi(); }

float getAngle(const sf::Vector2f& aVec);
float getDirection(const sf::Vector2f& aFrom, const sf::Vector2f& aTo);
float getVectorLength(const sf::Vector2f& aVec);
sf::Vector2f setVectorLength(const sf::Vector2f& aVec, float aLength);
sf::Vector2f operator*(const sf::Vector2f& aLhs, const sf::Vector2f& aRhs);

sf::Vector2f constrain(const sf::FloatRect& aRect, const sf::Vector2f& aVec);
