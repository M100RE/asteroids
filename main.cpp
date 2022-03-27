#include <iostream>
#include <random>

#include <glad/glad.h>
#include "entities/player/player.h"
#include "entities/asteroid/asteroid.h"

int window_height = 800;
int window_width = 800;

const float player_size = 0.04;

bool shooting = true;
int cooldown = 0;

int asteroids_in_frame = 7;

float player_vertices[] =
{
    -player_size, -player_size, 
     player_size,  0.0f,
    -player_size,  player_size 
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    window_width = width;
    window_height = height;
}


void input_handler(GLFWwindow* window, player& space_ship)
{
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        space_ship.accelerate();
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        space_ship.add_degree(8);
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        space_ship.add_degree(-8);
    }
    if(shooting && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        shooting = true;
        space_ship.shoot();
    }
}


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "title", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, window_width, window_height);

    player space_ship(0.0005, player_vertices, sizeof(player_vertices), nullptr, 0, "shaders/vertex.shader", "shaders/fragment.shader");
    std::vector<asteroid*> asteroids;

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    int counter = 0;

    while(!glfwWindowShouldClose(window))
    {
        counter++;
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        space_ship.update(window, window_width, window_height);
        int size = asteroids.size();
        for(int i = size; i < asteroids_in_frame - size; i++)
        {
            bool x_y = rand() % 2 == 0;
            float x = (x_y) ? (float)rand() / RAND_MAX * 2 - 1 : (rand() % 2 == 0) ? -1 : 1;
            float y = (!x_y) ? (float)rand() / RAND_MAX * 2 - 1 : (rand() % 2 == 0) ? -1 : 1;
            asteroids.push_back(new asteroid(((float)rand() / RAND_MAX * 2 - 1) / 100, ((float)rand() / RAND_MAX * 2 - 1) / 100, x, y, 1, 0));
        }
        for(int i = 0; i < asteroids.size(); i++)
        {
            asteroids[i]->update(window, window_width, window_height);
           if(asteroids[i]->receive_pos_x() > 1.2 || asteroids[i]->receive_pos_y() > 1.2 || asteroids[i]->receive_pos_x() < -1.2 || asteroids[i]->receive_pos_y() < -1.2)
            {
                asteroids[i]->destruct();
                delete asteroids[i];
                asteroids.erase(asteroids.begin() + i);
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        input_handler(window, space_ship);

        if(cooldown >= 10)
        {
            shooting = true;
            cooldown = 0;
        }
        cooldown++;
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
