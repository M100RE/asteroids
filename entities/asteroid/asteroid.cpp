#include "asteroid.h"

float vertices[] = 
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

asteroid::asteroid(float speed_x, float speed_y, float size, int stage)
    : entity(vertices, sizeof(vertices), indices, sizeof(indices), "shaders/vertex.shader", "shaders/fragment.shader")
{
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
        asteroid* splitter_1 = new asteroid(speed_x + speed_x * 0.5, speed_y, 0.5, 1);
        asteroid* splitter_2 = new asteroid(speed_x, speed_y + speed_y * 0.5, 0.5, 1);
        splitter_1->move(pos_x, pos_y);
        splitter_2->move(pos_x, pos_y);
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
}