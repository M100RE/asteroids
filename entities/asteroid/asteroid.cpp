#include "asteroid.h"

asteroid::asteroid(float speed_x, float speed_y, float* vertices, int vertices_size, unsigned int* indices, int indices_size, const char* vertex_path, const char* fragment_path)
    : entity(vertices, vertices_size, indices, indices_size, vertex_path, fragment_path)
{
    define_speed_x(speed_x);
    define_speed_y(speed_y);
}

void asteroid::split()
{

}

void asteroid::update(GLFWwindow* window, int window_width, int window_height)
{
    body.draw();
    add_move_speed();
}
