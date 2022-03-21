#pragma once

#include "../entity/entity.h"

class asteroid : entity
{
private:
public: 
    asteroid(float speed_x, float speed_y, float* vertices, int vertices_size, unsigned int* indices, int indices_size, const char* vertex_path, const char* fragment_path);

    void split();
    void update(GLFWwindow* window, int window_width, int window_height) override;
};
