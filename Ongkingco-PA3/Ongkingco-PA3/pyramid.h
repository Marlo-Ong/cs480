#ifndef PYRAMID_H
#define PYRAMID_H

#include "object.h"

class Pyramid : public Object
{
    public:
        Pyramid();
        void createVertices() override;
};

#endif
