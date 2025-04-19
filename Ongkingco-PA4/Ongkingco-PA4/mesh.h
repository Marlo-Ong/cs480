#ifndef MESH_H
#define MESH_H

#include "graphics_headers.h"

class Mesh
{
  public:
    Mesh();
    ~Mesh();
    bool loadModelFromFile(const char* path);
};

#endif /* MESH_H */
