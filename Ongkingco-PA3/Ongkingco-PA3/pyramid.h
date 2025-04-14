#ifndef PYRAMID_H
#define PYRAMID_H

#include "object.h"

class Pyramid : public Object
{
    public:
        Pyramid();
        Pyramid(glm::vec3 pivot, float angle, float scale);
        void createVertices() override;
};

#endif
