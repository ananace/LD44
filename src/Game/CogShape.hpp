#pragma once

#include <SFML/Graphics/Shape.hpp>
#include <cstdint>

namespace Game
{

class CogShape : public sf::Shape
{
public:
    explicit CogShape(float aRadius, float aToothHeight = 1.25f, size_t aToothCount = 10u, uint8_t aToothWidth = 2, bool aToothSlope = true);
    ~CogShape() = default;

    size_t getToothCount() const;
    void setToothCount(size_t aCount);
    float getToothHeight() const;
    void setToothHeight(float aHeight);
    uint8_t getToothWidth() const;
    void setToothWidth(uint8_t aSize);
    bool getToothSlope() const;
    void setToothSlope(bool aSlope);

    void setRadius(float aRadius);
    float getRadius() const;
    size_t getPointCount() const override;

    sf::Vector2f getPoint(size_t index) const override;

private:
    float m_circleRadius,
          m_toothHeight;
    size_t m_toothCount;

    uint8_t m_toothWidth;
    bool m_toothSlope;
};

}
