#ifndef TOOLS_H
#define TOOLS_H

#include <gladiator.h>
#include <vector>

#define ID1 37
#define ID2 40 

double reductionAngle(double x);
void go_to(Gladiator * gladiator, Position cons, Position pos);
float normRobot(float x, float y);
float distance(Position gladiatorPos, Position gladiatorAdvPos);
std::pair<float,byte> distanceToAllAdvs(Gladiator* gladiator);

// Function to know if a position is outside the current maze
bool isOutsideMaze(Gladiator* gladiator, const Position& pos);

// Function which return the Position of a Mazesquare
Position getSquarePosition(const MazeSquare* square);
float moduloPi(float a);

class Vector2
{
  public:
    Vector2() : _x(0.), _y(0.)
    {
    }
    Vector2(float x, float y) : _x(x), _y(y)
    {
    }

    float norm1() const
    {
        return abs(_x) + abs(_y);
    }
    float norm2() const
    {
        return std::sqrt(_x * _x + _y * _y);
    }
    void normalize()
    {
        _x /= norm2();
        _y /= norm2();
    }
    Vector2 normalized() const
    {
        Vector2 out = *this;
        out.normalize();
        return out;
    }

    Vector2 operator-(const Vector2 &other) const
    {
        return {_x - other._x, _y - other._y};
    }
    Vector2 operator+(const Vector2 &other) const
    {
        return {_x + other._x, _y + other._y};
    }
    Vector2 operator*(float f) const
    {
        return {_x * f, _y * f};
    }

    bool operator==(const Vector2 &other) const
    {
        return abs(_x - other._x) < 1e-5 && abs(_y - other._y) < 1e-5;
    }
    bool operator!=(const Vector2 &other) const
    {
        return !(*this == other);
    }

    float x() const
    {
        return _x;
    }
    float y() const
    {
        return _y;
    }

    float dot(const Vector2 &other) const
    {
        return _x * other._x + _y * other._y;
    }
    float cross(const Vector2 &other) const
    {
        return _x * other._y - _y * other._x;
    }
    float angle(const Vector2 &m) const
    {
        return std::atan2(cross(m), dot(m));
    }
    float angle() const
    {
        return std::atan2(_y, _x);
    }

  private:
    float _x, _y;
};
#endif
