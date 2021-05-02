#ifndef CAMERA_HH
#define CAMERA_HH

#include <glm/glm.hpp>

#include <graphics/shader.hh>


struct DefaultCamera
{
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 d = glm::vec3(0.0f, 0.0f, -1.0f);

    glm::mat4 get_view_matrix();
};


#endif