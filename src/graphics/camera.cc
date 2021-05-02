#include <graphics/camera.hh>

#include <glm/gtc/matrix_transform.hpp>


glm::mat4 DefaultCamera::get_view_matrix()
{
    return glm::lookAt(position, position + d, up);
}