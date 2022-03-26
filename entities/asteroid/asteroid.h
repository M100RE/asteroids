#pragma once

#include "../entity/entity.h"

class asteroid : entity
{
private:
public:
    asteroid(float speed_x, float speed_y, float size, int stage);

    void split();
    void update(GLFWwindow* window, int window_width, int window_height) override;
};