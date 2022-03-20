#include "entity.h"

entity::entity(float* vertices, int size_vertices, unsigned int* indices, int size_indices, const char* vertex_path, const char* fragment_path)
    : body(vertices, size_vertices, indices, size_indices, vertex_path, fragment_path),
    pos_x(0), pos_y(0)
{}

void entity::rotate(float degree)
{
    body.receive_shader().uniform1f("rotation", degree);
}

void entity::move(float x_coord, float y_coord)
{
    body.receive_shader().uniform2f("offset", x_coord, y_coord);
    pos_x = x_coord;
    pos_y = y_coord;
}

void entity::add_move(float x_direction, float y_direction)
{
    pos_x += x_direction;
    pos_y += y_direction;
    body.receive_shader().uniform2f("offset", pos_x, pos_y);
}

void entity::add_move_speed()
{
    pos_x += speed_x;
    pos_y += speed_y;
    body.receive_shader().uniform2f("offset", pos_x, pos_y);
}

void entity::define_speed_x(float speed)
{
    speed_x = speed;
}

void entity::define_speed_y(float speed)
{
    speed_y = speed;
}

float entity::receive_pos_x() const
{
    return pos_x;
}

float entity::receive_pos_y() const
{
    return pos_y;
}

void entity::update(GLFWwindow* window, int window_width, int window_height)
{    
    body.draw();
}
