#ifndef CUBE_H
#define CUBE_H

#include "object.h"

class Cube : public Object
{
    public:
        Cube();
        Cube(glm::vec3 pivot, float angle, float scale);
        void createVertices() override;
};

#endif
