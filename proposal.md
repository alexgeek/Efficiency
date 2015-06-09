# Refactoring Current Batched Cube Renderer to 6QUAD

Currently the OpenGL shader takes varying block positions in parallel and
renders a textured cube for its given cubemap.
This requires a shader for each block type which incurs overhead over a single
shader approach.

The proposed solution is to break down individual individual blocks into the
six faces of a cube. The face vertices can be quickly calculated in parallel
given its relative offset to a block center.
Each face is mapped to a texture ID that indexes a texture
atlas.



The decision is whether to buffer :

- A cube struct that contains a position and a texture ID for each face of the a cube
- A face struct that contains a position for each face and its texture ID

## Cube Struct

    typdef struct Cube {
      int X;
      int Y;
      int Z;
      unsigned int XPositive;
      unsigned int XNegative;
      unsigned int YPositive;
      unsigned int YNegative;
      unsigned int ZPositive;
      unsigned int ZNegative;
    }

The memory requirements in bits for n blocks is:

    (6+3)*n*sizeof(int) = 288*n

Per region that would be

    288*65536 = 18 874 368 ~ 2.4 MB

It requires n buffer calls and and 6 draw calls per frame to function.

## Face Struct

    typdef struct Face {
      int X;
      int Y;
      int Z;
      unsigned int Texture;
    }

The memory requirements in bits for n blocks as individual face structs is:

    6*4*n*sizeof(int) = 768*n

Per region that would be

    768*65536 = 50 331 648 ~ 6.3 MB

It requires 6n buffer calls and a draw call per frame.

## Summary

The `Face` struct approach requires over one and half times the memory
requirements of the `Cube` struct.

    sizeof(Face) = (5/3)*sizeof(Cube)
    sizeof(Face) ~ 1.7*sizeof(Cube)
