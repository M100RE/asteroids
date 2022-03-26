#include "player.h"
#include <math.h>

#include <iostream>

player::player(float acceleration, float* vertices, int size_vertices, unsigned int* indices, int size_indices, const char* vertex_path, const char* fragment_path)
    : entity(vertices, size_vertices, indices, size_indices, vertex_path, fragment_path),
    acceleration(acceleration)
{
    scale(1, 1);
}


float player::mouse_degree_relative_player(GLFWwindow* window, int window_width, int window_height)
{
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    x = x / (window_width / 2.0) - 1 - pos_x;
    y = (y / (window_height / 2.0) - 1) * -1.0 - pos_y;

    return (atan(y / x) + ((x >= 0) ? 0 : 3.14159265)) * (180 / 3.14159265);
}

float player::speed_x_mouse_direction()
{
    return cos(mouse_degree * (3.14159265f / 180.0f));
}

float player::speed_y_mouse_direction()
{
    return sin(mouse_degree * (3.14159265f / 180.0f));
}

void player::accelerate()
{
    speed_x += acceleration * speed_x_mouse_direction();
    speed_y += acceleration * speed_y_mouse_direction();
}

void player::define_degree(float degree)
{
    mouse_degree = degree;
}

void player::add_degree(float addition)
{
    mouse_degree += addition;
}

void player::update(GLFWwindow* window, int window_width, int window_height)
{
    //mouse_degree = mouse_degree_relative_player(window, window_width, window_height);
    rotate(mouse_degree);
    add_move_speed(); 
    
    if(pos_x < -1 || pos_x > 1)
        move(pos_x * -1, pos_y);
    if(pos_y < -1 || pos_y > 1)
        move(pos_x, pos_y * -1);

    body.draw(); 

    for(int i = 0; i < bullets.size(); i++)
    {
        bullets[i]->add_move_speed();
        bullets[i]->update(window, window_width, window_height);
        if(bullets[i]->receive_pos_x() > 1 || bullets[i]->receive_pos_x() < -1 || bullets[i]->receive_pos_y() < -1 || bullets[i]->receive_pos_y() > 1)
        {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        }
    }
}

void player::shoot()
{
    float bullet_vertices[] = 
    {
        -0.02f, -0.01f,
         0.02f, -0.01f,
         0.02f,  0.01f,
        -0.02f,  0.01f
    };
    unsigned int bullet_indices[] = 
    {
        0, 1, 2,
        0, 2, 3
    }; 

    entity* bullet = new entity(bullet_vertices, sizeof(bullet_vertices), bullet_indices, sizeof(bullet_indices), "shaders/vertex.shader", "shaders/fragment.shader");
    bullet->scale(1, 1);

    bullet->define_speed_x((abs(speed_x) + acceleration * 50) * speed_x_mouse_direction());
    bullet->define_speed_y((abs(speed_y) + acceleration * 50) * speed_y_mouse_direction());
    
    bullet->rotate(mouse_degree);
    bullet->move(pos_x + 0.04 * speed_x_mouse_direction(), pos_y + 0.04 * speed_y_mouse_direction());

    bullets.push_back(bullet);
}
