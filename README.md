# README #

Voxel-based engine written in C++ with Lua scripting.

Currently the engine render stores blocks of different types as integers
that are stored in hash maps (with a custom hashing function) for O(1) access.

Blocks are drawn by supplying the block texture and the positions of all blocks
of that type using instancing.

The plan is to a texture atlas to reduce the number of draw calls but this will
take some time. I may also implement a marching cubes style surface extractor
that will help in avoiding sending occluded voxels to the GPU.

### Compiling ###

This project used to compile from a simple Makefile but the build process
became much more complicated as time went on.

It is now built via cmake and has been tested on Windows and Linux. I recommend
[Clion](https://www.jetbrains.com/clion/) with the
[MinGW](http://www.mingw.org/) toolchain for Windows users.

To compile without an IDE, it should suffice to do the following from the source
directory at the terminal:

```bash
mkdir build && cd build
cmake ../ && cmake --build .
```

Note that C++11 is required but only for more accurate timing with `std::chrono`.
The requirement of C++11 will be moved to a separate debugging build target in
the future.
