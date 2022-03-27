#include "asteroid.h"
#include <iostream>

float asteroid_vertices[] = 
{
    -0.1f, -0.1f,
     0.1f, -0.1f,
     0.1f,  0.1f,
    -0.1f,  0.1f
};

unsigned int indices[] = 
{
    0, 1, 2,
    0, 2, 3
};

asteroid::asteroid(float speed_x, float speed_y, float pos_x, float pos_y, float size, int stage)
    : entity(asteroid_vertices, sizeof(asteroid_vertices), indices, sizeof(indices), "shaders/vertex.shader", "shaders/fragment.shader")
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
        asteroid* splitter_1 = new asteroid(speed_x + speed_x * 0.5, speed_y, pos_x, pos_y, 0.5, 1);
        asteroid* splitter_2 = new asteroid(speed_x, speed_y + speed_y * 0.5, pos_x, pos_y, 0.5, 1);

        splitters.push_back(splitter_1);
        splitters.push_back(splitter_2);

        splitted = true;
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
    std::cout << "f\n";
}