#include "CogShape.hpp"
#include "../Util.hpp"

#include <cstdio>

using Game::CogShape;

CogShape::CogShape(float aRadius, float aToothHeight, size_t aToothCount, uint8_t aToothWidth, bool aToothSlope)
    : m_circleRadius(aRadius)
    , m_toothHeight(aToothHeight)
    , m_toothCount(aToothCount)
    , m_toothWidth(aToothWidth)
    , m_toothSlope(aToothSlope)
{
    update();
}

size_t CogShape::getToothCount() const
{
    return m_toothCount;
}
void CogShape::setToothCount(size_t aCount)
{
    m_toothCount = aCount;
    update();
}
float CogShape::getToothHeight() const
{
    return m_toothHeight;
}
void CogShape::setToothHeight(float aHeight)
{
    m_toothHeight = aHeight;
    update();
}
uint8_t CogShape::getToothWidth() const
{
    return m_toothWidth;
}
void CogShape::setToothWidth(uint8_t aWidth)
{
    m_toothWidth = aWidth;
    update();
}
bool CogShape::getToothSlope() const
{
    return m_toothSlope;
}
void CogShape::setToothSlope(bool aSlope)
{
    m_toothSlope = aSlope;
    update();
}

void CogShape::setRadius(float aRadius)
{
    m_circleRadius = aRadius;
}
float CogShape::getRadius() const
{
    return m_circleRadius;
}
size_t CogShape::getPointCount() const
{
    return m_toothCount * 8;
}

sf::Vector2f CogShape::getPoint(size_t aIndex) const
{
    const size_t offset = getPointCount() / m_toothCount;
    float mult = 1.f;

    if (aIndex % offset <= m_toothWidth ||
        offset - (aIndex % offset) <= m_toothWidth)
    {
        mult = m_toothHeight;

        if (m_toothSlope &&
            (aIndex % offset == m_toothWidth ||
             offset - (aIndex % offset) == m_toothWidth))
            mult = (3.f + m_toothHeight * 1) / 4.f;
    }

    // TODO: slope

    float angle = aIndex * 2.f * Pi() / getPointCount() - Pi() / 2.f;

    float multrad = m_circleRadius * mult;
    float x = cos(angle) * multrad;
    float y = sin(angle) * multrad;

    return { m_circleRadius + x, m_circleRadius + y };
}
