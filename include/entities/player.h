#pragma once

#include "entity.h"
#include <vector>
#include <GLFW/glfw3.h>

class player : public entity
{
private:
    float acceleration = 0.0003;
    float mouse_degree;

    std::vector<entity*> bullets;
    std::vector<int> bullet_despawn_time;

    float mouse_degree_relative_player(GLFWwindow* window, int window_width, int window_height);
    float speed_x_mouse_direction();
    float speed_y_mouse_direction();
public:
    player(float acceleration);
    void accelerate();
    void define_degree(float degree);
    void add_degree(float addition);
    void update (GLFWwindow* window, int window_width, int window_height) override;
    void shoot();
    std::vector<entity*> receive_bullets() const;
};
