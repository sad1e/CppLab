#pragma once

#include <cstdint>

struct FArchive
{
    void Serialize(void* V, int64_t Length) {}

    friend FArchive& operator<<(FArchive& Ar, int32_t V);
    friend FArchive& operator<<(FArchive& Ar, float V);
};

struct float3
{
    float x, y, z;
    friend FArchive& operator<<(FArchive& Ar, float3& f3)
    {

    }
};

struct IShape
{
    virtual ~IShape() {}

    virtual int GetVertexCount() = 0;
};

struct Sphere : public IShape
{
    int GetVertexCount() override { return 128; }

    float3 center;
    float radius;

    void Serialize(FArchive& Ar)
    {
        Ar << center;
        Ar << radius;
    }
};

struct Cube : public IShape
{
    int GetVertexCount() override { return 8; }

};

struct Cylinder : public IShape
{
    int GetVertexCount() override { return 64; }
};

class IShapeVisitor
{
    void VisitSphere(Sphere s) {}

    void VisitCube(Cube c) {}

    void VisitCylinder(Cylinder c) {}
};