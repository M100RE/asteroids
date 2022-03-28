#include "entities/asteroid.h"
#include <iostream>

const float asteroid_size = 0.1;

float asteroid_vertices[] = 
{
    -asteroid_size, -asteroid_size,
     asteroid_size, -asteroid_size,
     asteroid_size,  asteroid_size,
    -asteroid_size,  asteroid_size
};

unsigned int indices[] = 
{
    0, 1, 2,
    0, 2, 3
};

asteroid::asteroid(float speed_x, float speed_y, float pos_x, float pos_y, float size, int stage, int cooldown)
    : entity(asteroid_vertices, sizeof(asteroid_vertices), indices, sizeof(indices), "../shaders/vertex.shader", "../shaders/fragment.shader"),
    scaling(size), cooldown(cooldown), stage(stage)
{
    move(pos_x, pos_y);
    scale(size, size);
    define_speed_x(speed_x);
    define_speed_y(speed_y);
}

asteroid::~asteroid()
{
    destruct();
}

void asteroid::split()
{
    if(!splitted)
    {
        asteroid* splitter_1 = new asteroid(speed_x + speed_x * 0.5, speed_y, pos_x, pos_y, scaling * 0.8, stage + 1, 10);
        asteroid* splitter_2 = new asteroid(speed_x, speed_y + speed_y * 0.5, pos_x, pos_y, scaling * 0.8, stage + 1, 10);

        splitters.push_back(splitter_1);
        splitters.push_back(splitter_2);

        splitted = true;
    }
}

bool asteroid::check_collisions(std::vector<entity*> bullets)
{
    if(cooldown <= 0)
    {
        float real_size = asteroid_size * scaling;
        for(int i = 0; i < bullets.size(); i++)
        {
            if(bullets[i]->receive_pos_x() < real_size + pos_x
                && bullets[i]->receive_pos_x() > -real_size + pos_x
                && bullets[i]->receive_pos_y() < real_size + pos_y
                && bullets[i]-> receive_pos_y() > -real_size + pos_y)
                {
                    if(stage < 2)
                    {
                        split();
                        return false;
                    }
                    else
                    {
                        return true;
                    }
                }
        }
        return false;
    }
    else
    {
        cooldown--;
        return false;
    }
}

bool asteroid::check_all_collisions(std::vector<entity*> bullets)
{
    if(!splitted)
    {
        return check_collisions(bullets);
    }
    else
    {
        bool returnable = true;
        for(int i = 0; i < splitters.size(); i++)
        {
            if(!splitters[i]->check_all_collisions(bullets))
            {
                 returnable = false;
            }
            else
            {
                delete splitters[i];
                splitters.erase(splitters.begin() + i);
            }
        }
        return returnable;
    }
}

bool asteroid::out_of_bounds(float bound_x, float bound_y)
{
    if(!splitted)
    {
        if(pos_x > bound_x || pos_x < -bound_x || pos_y > bound_y || pos_y < -bound_y)
        {
            destruct();
            return true;
        }
        return false;
    }
    else
    {
        for(int i = 0; i < splitters.size(); i++)
        {
            if(!splitters[i]->out_of_bounds(bound_x, bound_y))
            {
                return false;
            }
        }
        return true;
    }
}

void asteroid::update(GLFWwindow* window, int window_width, int window_height)
{
    if(!splitted)
    {
        body.draw();
        add_move_speed();
    }
    
    for(int i = 0; i < splitters.size(); i++)
    {
        splitters[i]->update(window, window_width, window_height);
    }
}

void asteroid::destruct()
{
    for(int i = 0; i < splitters.size(); i++)
    {
        splitters[i]->destruct();
        delete splitters[i];
    }
    splitters.clear();
}