#include "Util.hpp"

float getAngle(const sf::Vector2f& aVec)
{
    return atan2(aVec.y, aVec.x);
}
float getDirection(const sf::Vector2f& aFrom, const sf::Vector2f& aTo)
{
    return getAngle(aTo - aFrom);
}
float getVectorLength(const sf::Vector2f& aVec)
{
    return sqrt(aVec.x * aVec.x + aVec.y * aVec.y);
}

sf::Vector2f setVectorLength(const sf::Vector2f& aVec, float aLength)
{
    float curLen = getVectorLength(aVec);
    if (aLength == 0 || curLen == 0)
        return {};
    return aVec * (aLength / curLen);
}

sf::Vector2f operator*(const sf::Vector2f& aLhs, const sf::Vector2f& aRhs)
{
    return { aLhs.x * aRhs.x, aLhs.y * aRhs.y };
}

sf::Vector2f constrain(const sf::FloatRect& aRect, const sf::Vector2f& aVec)
{
    return { std::min(aRect.left + aRect.width, std::max(aRect.left, aVec.x)), std::min(aRect.top + aRect.height, std::max(aRect.top, aVec.y)) };
}
