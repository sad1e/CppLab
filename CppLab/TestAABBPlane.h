#include <iostream>
#include <cmath>

struct vec3
{
    float x, y, z;

    //vec3() = default;
    // vec3(const vec3& v) : x(v.x), y(v.y), z(v.z) {}

    vec3 operator+(const vec3& v)
    {
        return { .x = x + v.x, .y = y + v.y, .z = z + v.z };
    }

    vec3 operator-(const vec3& v)
    {
        return { .x = x - v.x, .y = y - v.y, .z = z - v.z };
    }

    vec3 operator*(float v)
    {
        return { .x = x * v, .y = y * v, .z = z * v };
    }

    // cross product.
    vec3 operator^(const vec3& v) const
    {
        return {
            .x = y * v.z - z * v.y,
            .y = z * v.x - x * v.z,
            .z = z * v.y - y * v.x
        };
    }

    // dot product.
    float operator|(const vec3& v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    vec3 normalize()
    {
        const float invsqrt = 1.0f / std::sqrt(x * x + y * y + z * z);
        return { .x = x * invsqrt, .y = y * invsqrt, .z = z * invsqrt };
    }

    vec3 abs()
    {
        return { .x = std::abs(x), .y = std::abs(y), .z = std::abs(z) };
    }
};

struct plane
{
    plane() = default;
    plane(vec3 b, vec3 n) : d(n), w(b | n) {}

    vec3 d;
    float w;

    float dot(const vec3& v) const
    {
        return (d | v) - w;
    }
};

struct aabb
{
    vec3 min, max;

    vec3 center() { return (min + max) * 0.5; }
};

int TestAABBPlane(aabb b, plane p)
{
    // Convert AABB to center-extents representation
    vec3 c = (b.max + b.min) * 0.5f; // Compute AABB center
    vec3 e = b.max - c; // Compute positive extents

    // Compute the projection interval radius of b onto L(t) = b.c + t * p.n
    // float r = e[0] * std::abs(p.n[0]) + e[1] * std::abs(p.n[1]) + e[2] * std::abs(p.n[2]);
    float r = e | p.d.abs();

    // Compute distance of box center from plane
    // float s = Dot(p.n, c) - p.d;
    float s = (p.d | c) - p.w;

    // Intersection occurs when distance s falls within [-r,+r] interval
    return std::abs(s) <= r;
}
