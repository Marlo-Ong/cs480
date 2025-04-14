#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"

class Object
{
    public:
        ~Object();

        void Initialize(GLint posAttribLoc, GLint colAttribLoc);
        void Update(unsigned int dt);
        void Render(GLint posAttribLoc, GLint colAttribLoc);

        // Defines object vertices and triangle indexes
        virtual void createVertices() = 0;

        void setupModelMatrix(glm::vec3 pivot, float angle, float scale);
        glm::mat4 GetModel();

        void setSpeed(glm::vec3 spd) { m_speed = spd; }
        void setAngularSpeed(glm::vec3 spd) { m_angSpeed = spd; }

    protected:
        // Define object in space
        glm::mat4 model;
        std::vector<Vertex> Vertices;
        std::vector<unsigned int> Indices;

        // Define vertex array and vertex/index buffer objects
        GLuint vao;
        GLuint VB;
        GLuint IB;

        // Define object speed and initial rotation angle
        glm::vec3 m_speed = glm::vec3(0., 0., 0.);
        glm::vec3 m_angSpeed = glm::vec3(0., 0., 0.);
        glm::vec3 pivotLocation = glm::vec3(0., 0., 0.);
        float angle;
};

#endif /* OBJECT_H */
