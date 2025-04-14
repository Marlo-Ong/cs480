#ifndef CUBE_H
#define CUBE_H

#include "object.h"

class Cube : public Object
{
    public:
        Cube();
        void createVertices() override;
};

#endif
