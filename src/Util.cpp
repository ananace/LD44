#include "Util.hpp"

sf::Vector2f operator*(const sf::Vector2f& aLhs, const sf::Vector2f& aRhs)
{
    return { aLhs.x * aRhs.x, aLhs.y * aRhs.y };
}
