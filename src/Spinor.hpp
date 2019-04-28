#pragma once

struct Spinor
{
    static Spinor slerp(const Spinor& aFrom, const Spinor& aTo, float aDelta);
    static float slerpAngle(float aStart, float aEnd, float aDelta);

    Spinor();
    Spinor(float aAngle);
    Spinor(float aReal, float aComplex);
    Spinor(const Spinor&) = default;
    ~Spinor() = default;

    bool operator==(const Spinor& aRhs);

    Spinor& operator +=(const Spinor& aRhs);
    Spinor& operator -=(const Spinor& aRhs);
    Spinor& operator *=(const Spinor& aRhs);
    Spinor& operator /=(const Spinor& aRhs);
    Spinor& operator *=(float aFactor);
    Spinor& operator /=(float aFactor);

    Spinor operator +(const Spinor& aRhs) const;
    Spinor operator -(const Spinor& aRhs) const;
    Spinor operator *(const Spinor& aRhs) const;
    Spinor operator /(const Spinor& aRhs) const;
    Spinor operator *(float aFactor) const;
    Spinor operator /(float aFactor) const;

    float getAngle() const;
    float getLength() const;

    void setAngle(float aAngle);
    void setLength(float aLength);

    float Real, Complex;
};
