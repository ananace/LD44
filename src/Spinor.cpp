#include "Spinor.hpp"

#include <cmath>

Spinor Spinor::slerp(const Spinor& aFrom, const Spinor& aTo, float aDelta)
{
    float tr, tc, cosom, scale0, scale1;
    cosom = aFrom.Real * aTo.Real + aFrom.Complex * aTo.Complex;

    if (cosom < 0)
    {
        cosom = -cosom;
        tc = -aTo.Complex;
        tr = -aTo.Real;
    }
    else
    {
        tc = aTo.Complex;
        tr = aTo.Real;
    }

    if (1 - cosom > 0.001f)
    {
        float omega = std::acos(cosom);
        float sinom = std::sin(omega);
        scale0 = sin((1 - aDelta) * omega) / sinom;
        scale1 = sin(aDelta * omega) / sinom;
    }
    else
    {
        scale0 = 1 - aDelta;
        scale1 = aDelta;
    }

    return Spinor(scale0 * aFrom.Real + scale1 * tr, scale0 * aFrom.Complex + scale1 * tc);
}

float Spinor::slerpAngle(float aStart, float aEnd, float aDelta)
{
    Spinor start, end;
    start.Real = cos(aStart / 2);
    start.Complex = sin(aStart / 2);
    end.Real = cos(aEnd / 2);
    end.Complex = sin(aEnd / 2);

    float tr, tc, omega, cosom, sinom, s0, s1;

    cosom = start.Real * end.Real + start.Complex * end.Complex;

    if (cosom < 0)
    {
        cosom = -cosom;
        tc = -end.Complex;
        tr = -end.Real;
    }
    else
    {
        tc = end.Complex;
        tr = end.Real;
    }

    if (1 - cosom > 0.001)
    {
        omega = acos(cosom);
        sinom = sin(omega);
        s0 = sin((1 - aDelta) * omega) / sinom;
        s1 = sin(aDelta * omega) / sinom;
    }
    else
    {
        s0 = 1 - aDelta;
        s1 = aDelta;
    }

    Spinor ret;
    ret.Complex = s0 * start.Complex + s1 * tc;
    ret.Real = s0 * start.Real + s1 * tr;

    return atan2(ret.Complex, ret.Real) * 2;
}

Spinor::Spinor()
    : Real(0)
    , Complex(0)
{ }
Spinor::Spinor(float ang)
    : Real(std::cos(ang))
    , Complex(std::sin(ang))
{ }
Spinor::Spinor(float r, float c)
    : Real(r)
    , Complex(c)
{ }

Spinor& Spinor::operator +=(const Spinor& aRhs)
{
    Real += aRhs.Real; Complex += aRhs.Complex;
    return *this;
}
Spinor& Spinor::operator -=(const Spinor& aRhs)
{
    Real -= aRhs.Real; Complex -= aRhs.Complex;
    return *this;
}
Spinor& Spinor::operator *=(const Spinor& aRhs)
{
    float newReal = Real * aRhs.Real - Complex * aRhs.Complex;
    Complex = Real * aRhs.Complex + Complex * aRhs.Real;
    Real = newReal;

    return *this;
}
Spinor& Spinor::operator /=(const Spinor& aRhs)
{
    float len = aRhs.Real * aRhs.Real + aRhs.Complex * aRhs.Complex;
    if (len == 0)
        return *this;

    float newReal = (Real * aRhs.Real - Complex * aRhs.Complex) / len;
    Complex = (Real * aRhs.Complex + Complex * aRhs.Real) / len;
    Real = newReal;

    return *this;
}
Spinor& Spinor::operator *=(float val)
{
    Real *= val; Complex *= val;
    return *this;
}
Spinor& Spinor::operator /=(float val)
{
    Real /= val; Complex /= val;
    return *this;
}

Spinor Spinor::operator +(const Spinor& aRhs) const
{
    return Spinor(Real + aRhs.Real, Complex + aRhs.Complex);
}
Spinor Spinor::operator -(const Spinor& aRhs) const
{
    return Spinor(Real - aRhs.Real, Complex - aRhs.Complex);
}
Spinor Spinor::operator *(const Spinor& aRhs) const
{
    return Spinor(Real * aRhs.Real - Complex * aRhs.Complex, Real * aRhs.Complex + Complex * aRhs.Real);
}
Spinor Spinor::operator /(const Spinor& aRhs) const
{
    float len = aRhs.Real * aRhs.Real + aRhs.Complex * aRhs.Complex;
    if (len == 0)
    return *this;

    return Spinor((Real * aRhs.Real - Complex * aRhs.Complex) / len, (Real * aRhs.Complex + Complex * aRhs.Real) / len);
}
Spinor Spinor::operator *(float val) const
{
    return Spinor(Real * val, Complex * val);
}
Spinor Spinor::operator /(float val) const
{
    return Spinor(Real / val, Complex / val);
}

float Spinor::getAngle() const
{
    return std::atan2(Complex, Real) * 2;
}
float Spinor::getLength() const
{
    return std::sqrt(Real * Real + Complex * Complex);
}

void Spinor::setAngle(float ang)
{
    float len = std::sqrt(Real * Real + Complex * Complex);
    Real = cos(ang) * len;
    Complex = sin(ang) * len;
}
void Spinor::setLength(float len)
{
    float oldLen = std::sqrt(Real * Real + Complex * Complex);
    if (oldLen == 0)
        return;

    float newLen = len / oldLen;
    Real *= newLen;
    Complex *= newLen;
}
