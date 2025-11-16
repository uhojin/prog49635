#ifndef PROCEDURAL_GEOMETRY_H
#define PROCEDURAL_GEOMETRY_H

#include "standardincludes.h"

class ProceduralGeometry
{
public:
    // Generate sphere vertex data (positions, normals, UVs interleaved)
    // Returns vector of floats in format: [x, y, z, nx, ny, nz, u, v, ...]
    static vector<GLfloat> GenerateSphere(float radius, int segments, int rings);

    // Generate cube vertex data (positions, normals, UVs interleaved)
    // Returns vector of floats in format: [x, y, z, nx, ny, nz, u, v, ...]
    static vector<GLfloat> GenerateCube(float size);
};

#endif // PROCEDURAL_GEOMETRY_H
