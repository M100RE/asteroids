#include "asteroid.h"

float vertices[] = 
{

};

unsigned int indices[] = 
{

};

asteroid::asteroid(float speed_x, float speed_y, float size, int stage)
    : entity(vertices, sizeof(vertices), indices, sizeof(indices), "shaders/vertex.shader", "shaders/fragment.shader")
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