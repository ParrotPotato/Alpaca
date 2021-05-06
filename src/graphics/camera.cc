#include <graphics/camera.hh>

#include <glm/gtc/matrix_transform.hpp>

#include <core/input.hh>
#include <imgui.h>


glm::mat4 DefaultCamera::get_view_matrix()
{
    return glm::lookAt(position, position + d, up);
}

void DefaultCamera::update_camera_position(InputHandler & input)
{
    static float imm_mouse_sensitivity = 0.1f;
    static float imm_camera_movement = 0.1f;
    static float yaw = -90.f;
    static float pitch = 0;

    {
        ImGui::Begin("Camera Motion");
        ImGui::SliderFloat("mouse sensitivity", &imm_mouse_sensitivity, 0.1f, 0.9f);
        ImGui::SliderFloat("key sensitivity", &imm_camera_movement, 0.1f, 2.f);
        ImGui::End();
    }

    if (input.keyboard.keydown(SDLK_w))
    {
        position += d * imm_camera_movement;
    }
    if(input.keyboard.keydown(SDLK_s))
    {
        position += d * (-imm_camera_movement);
    }
    if(input.keyboard.keydown(SDLK_a))
    {
        position += glm::normalize(glm::cross(d, up)) * (-imm_camera_movement);
    }
    if(input.keyboard.keydown(SDLK_d))
    {
        position += glm::normalize(glm::cross(d, up)) * imm_camera_movement;
    }

    if(input.keyboard.keydown(SDLK_LSHIFT))
    {
        if(input.mouse.mouse_motion)
        {
            float sensitivity = imm_mouse_sensitivity;

            float xoffset = input.mouse.relx * sensitivity;
            float yoffset = input.mouse.rely * sensitivity;

            yaw += xoffset;
            pitch += yoffset;

            if(pitch > 89.0f) pitch = 89.0f;
            else if(pitch < -89.0) pitch = -89.0f;

            glm::vec3 front;

            front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            front.y = -sin(glm::radians(pitch));
            front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

            d = front;
        }
    }
}