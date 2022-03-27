#pragma once

#include "../entity/entity.h"
#include <vector>

class asteroid : public entity
{
private:
    std::vector<asteroid*> splitters;
    int stage;
    float scaling;
    bool splitted = false;
    int cooldown;

    bool check_collisions(std::vector<entity*> bullets);
public:
    asteroid(float speed_x, float speed_y, float pos_x, float pos_y, float size, int stage, int cooldown);
    ~asteroid();

    void split();
    void update(GLFWwindow* window, int window_width, int window_height) override;
    bool check_all_collisions(std::vector<entity*> bullets);
    bool out_of_bounds(float bound_x, float bound_y);
    void destruct();
};