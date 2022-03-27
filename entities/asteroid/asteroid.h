#pragma once

#include "../entity/entity.h"
#include <vector>

class asteroid : entity
{
private:
    std::vector<asteroid*> splitters;
    bool splitted = false;
public:
    asteroid(float speed_x, float speed_y, float size, int stage);
    ~asteroid();

    void split();
    void update(GLFWwindow* window, int window_width, int window_height) override;
    void destruct();
};