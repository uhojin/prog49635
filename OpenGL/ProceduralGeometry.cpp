#include "ProceduralGeometry.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

vector<GLfloat> ProceduralGeometry::GenerateSphere(float radius, int segments, int rings)
{
    vector<GLfloat> vertices;

    // Generate vertices
    for (int ring = 0; ring <= rings; ring++)
    {
        float phi = M_PI * float(ring) / float(rings);
        float sinPhi = sin(phi);
        float cosPhi = cos(phi);

        for (int seg = 0; seg <= segments; seg++)
        {
            float theta = 2.0f * M_PI * float(seg) / float(segments);
            float sinTheta = sin(theta);
            float cosTheta = cos(theta);

            // Position
            float x = radius * sinPhi * cosTheta;
            float y = radius * cosPhi;
            float z = radius * sinPhi * sinTheta;

            // Normal (for a sphere centered at origin, normal = normalized position)
            float nx = sinPhi * cosTheta;
            float ny = cosPhi;
            float nz = sinPhi * sinTheta;

            // UV coordinates
            float u = float(seg) / float(segments);
            float v = float(ring) / float(rings);

            // Add vertex data (position, normal, uv)
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
            vertices.push_back(nx);
            vertices.push_back(ny);
            vertices.push_back(nz);
            vertices.push_back(u);
            vertices.push_back(v);
        }
    }

    // Generate triangle data (convert to triangles)
    vector<GLfloat> triangles;

    for (int ring = 0; ring < rings; ring++)
    {
        for (int seg = 0; seg < segments; seg++)
        {
            int current = ring * (segments + 1) + seg;
            int next = current + segments + 1;

            // First triangle
            int i1 = current;
            int i2 = next;
            int i3 = current + 1;

            // Add first triangle vertices
            for (int i = 0; i < 8; i++) triangles.push_back(vertices[i1 * 8 + i]);
            for (int i = 0; i < 8; i++) triangles.push_back(vertices[i2 * 8 + i]);
            for (int i = 0; i < 8; i++) triangles.push_back(vertices[i3 * 8 + i]);

            // Second triangle
            int i4 = current + 1;
            int i5 = next;
            int i6 = next + 1;

            // Add second triangle vertices
            for (int i = 0; i < 8; i++) triangles.push_back(vertices[i4 * 8 + i]);
            for (int i = 0; i < 8; i++) triangles.push_back(vertices[i5 * 8 + i]);
            for (int i = 0; i < 8; i++) triangles.push_back(vertices[i6 * 8 + i]);
        }
    }

    return triangles;
}

vector<GLfloat> ProceduralGeometry::GenerateCube(float size)
{
    float half = size / 2.0f;
    vector<GLfloat> vertices;

    // Cube has 6 faces, each face has 2 triangles (6 vertices)
    // Format: position (3), normal (3), UV (2)

    // Front face (+Z)
    GLfloat frontFace[] = {
        // Triangle 1
        -half, -half,  half,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
         half, -half,  half,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
         half,  half,  half,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        // Triangle 2
        -half, -half,  half,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
         half,  half,  half,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        -half,  half,  half,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
    };

    // Back face (-Z)
    GLfloat backFace[] = {
        // Triangle 1
         half, -half, -half,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
        -half, -half, -half,  0.0f, 0.0f, -1.0f,  1.0f, 0.0f,
        -half,  half, -half,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
        // Triangle 2
         half, -half, -half,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
        -half,  half, -half,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
         half,  half, -half,  0.0f, 0.0f, -1.0f,  0.0f, 1.0f,
    };

    // Right face (+X)
    GLfloat rightFace[] = {
        // Triangle 1
         half, -half,  half,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
         half, -half, -half,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
         half,  half, -half,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        // Triangle 2
         half, -half,  half,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
         half,  half, -half,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
         half,  half,  half,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    };

    // Left face (-X)
    GLfloat leftFace[] = {
        // Triangle 1
        -half, -half, -half, -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        -half, -half,  half, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        -half,  half,  half, -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        // Triangle 2
        -half, -half, -half, -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        -half,  half,  half, -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        -half,  half, -half, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    };

    // Top face (+Y)
    GLfloat topFace[] = {
        // Triangle 1
        -half,  half,  half,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
         half,  half,  half,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
         half,  half, -half,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        // Triangle 2
        -half,  half,  half,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
         half,  half, -half,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        -half,  half, -half,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
    };

    // Bottom face (-Y)
    GLfloat bottomFace[] = {
        // Triangle 1
        -half, -half, -half,  0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
         half, -half, -half,  0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
         half, -half,  half,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
        // Triangle 2
        -half, -half, -half,  0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
         half, -half,  half,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
        -half, -half,  half,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
    };

    // Combine all faces
    vertices.insert(vertices.end(), frontFace, frontFace + 48);
    vertices.insert(vertices.end(), backFace, backFace + 48);
    vertices.insert(vertices.end(), rightFace, rightFace + 48);
    vertices.insert(vertices.end(), leftFace, leftFace + 48);
    vertices.insert(vertices.end(), topFace, topFace + 48);
    vertices.insert(vertices.end(), bottomFace, bottomFace + 48);

    return vertices;
}
