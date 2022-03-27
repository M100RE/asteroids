#include "player.h"
#include <math.h>

#include <iostream>

const float player_size = 0.04;
const float despawn_time_bullets = 100;
const float speed_bullets = 50;

float vertices[] = 
{
    -player_size, -player_size,
     player_size,  0.0f,
    -player_size,  player_size
};

player::player(float acceleration)
    : entity(vertices, sizeof(vertices), nullptr, 0, "shaders/vertex.shader", "shaders/fragment.shader"),
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
        bullet_despawn_time[i]++;

        bullets[i]->add_move_speed();
        bullets[i]->update(window, window_width, window_height);

        if(bullets[i]->receive_pos_x() > 1 || bullets[i]->receive_pos_x() < -1)
            bullets[i]->move(bullets[i]->receive_pos_x() * -1, bullets[i]->receive_pos_y() * -1);
        if(bullets[i]->receive_pos_y() < -1 || bullets[i]->receive_pos_y() > 1)
            bullets[i]->move(bullets[i]->receive_pos_x(), bullets[i]->receive_pos_y() * -1);

        if(bullet_despawn_time[i] > despawn_time_bullets)
        {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
            bullet_despawn_time.erase(bullet_despawn_time.begin() + i);
        }
    }
}

void player::shoot()
{
    float bullet_vertices[] = 
    {
        -0.01f, -0.01f,
         0.01f, -0.01f,
         0.01f,  0.01f,
        -0.01f,  0.01f
    };
    unsigned int bullet_indices[] = 
    {
        0, 1, 2,
        0, 2, 3
    }; 

    entity* bullet = new entity(bullet_vertices, sizeof(bullet_vertices), bullet_indices, sizeof(bullet_indices), "shaders/vertex.shader", "shaders/fragment.shader");
    bullet->scale(1, 1);

    bullet->define_speed_x((abs(speed_x) + acceleration * speed_bullets) * speed_x_mouse_direction());
    bullet->define_speed_y((abs(speed_y) + acceleration * speed_bullets) * speed_y_mouse_direction());
    
    bullet->rotate(mouse_degree);
    bullet->move(pos_x + 0.04 * speed_x_mouse_direction(), pos_y + 0.04 * speed_y_mouse_direction());

    bullets.push_back(bullet);
    bullet_despawn_time.push_back(0);
}
