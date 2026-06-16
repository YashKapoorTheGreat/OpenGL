#pragma once

// Basic Cube Data
static float verticesSmooth[48] = {
    // Position coordinates  |  Normal vectors (nx, ny, nz)
    -0.5f, -0.5f, 0.5f, -0.57735f, -0.57735f, 0.57735f,   // 0: Front-Bottom-Left
    0.5f, -0.5f, 0.5f, 0.57735f, -0.57735f, 0.57735f,     // 1: Front-Bottom-Right
    0.5f, 0.5f, 0.5f, 0.57735f, 0.57735f, 0.57735f,       // 2: Front-Top-Right
    -0.5f, 0.5f, 0.5f, -0.57735f, 0.57735f, 0.57735f,     // 3: Front-Top-Left
    -0.5f, -0.5f, -0.5f, -0.57735f, -0.57735f, -0.57735f, // 4: Back-Bottom-Left
    0.5f, -0.5f, -0.5f, 0.57735f, -0.57735f, -0.57735f,   // 5: Back-Bottom-Right
    0.5f, 0.5f, -0.5f, 0.57735f, 0.57735f, -0.57735f,     // 6: Back-Top-Right
    -0.5f, 0.5f, -0.5f, -0.57735f, 0.57735f, -0.57735f    // 7: Back-Top-Left
};

static unsigned int cubeIndicesSmooth[] = {
    0, 1, 2, 2, 3, 0, // Front Face
    1, 5, 6, 6, 2, 1, // Right Face
    7, 6, 5, 5, 4, 7, // Back Face
    4, 0, 3, 3, 7, 4, // Left Face
    3, 2, 6, 6, 7, 3, // Top Face
    4, 5, 1, 1, 0, 4  // Bottom Face
};

static float verticesFlat[144] = {
    // Position coordinates   |  Normal vectors (nx, ny, nz)

    // Front Face (Normal: Z+)
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // 0
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,  // 1
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,   // 2
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,  // 3

    // Right Face (Normal: X+)
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,  // 4
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // 5
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  // 6
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,   // 7

    // Back Face (Normal: Z-)
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,  // 8
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,   // 9
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,  // 10
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, // 11

    // Left Face (Normal: X-)
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, // 12
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,  // 13
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,   // 14
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,  // 15

    // Top Face (Normal: Y+)
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,  // 16
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,   // 17
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // 18
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // 19

    // Bottom Face (Normal: Y-)
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, // 20
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,  // 21
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,   // 22
    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f   // 23
};

static unsigned int cubeIndicesFlat[] = {
    0, 1, 2, 2, 3, 0,       // Front Face
    4, 5, 6, 6, 7, 4,       // Right Face
    8, 9, 10, 10, 11, 8,    // Back Face
    12, 13, 14, 14, 15, 12, // Left Face
    16, 17, 18, 18, 19, 16, // Top Face
    20, 21, 22, 22, 23, 20  // Bottom Face
};
