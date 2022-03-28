#include <iostream>
#include <random>

#include <glad/glad.h>
#include "entities/player.h"
#include "entities/asteroid.h"

int window_height = 800;
int window_width = 800;

bool shooting = true;
int cooldown = 0;

float player_size = 0.05;

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
        shooting = false;
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

    player space_ship(0.0005);
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
            int right_left1 = (rand() % 2 == 0) ? -1 : 1;
            int right_left2 = (rand() % 2 == 0) ? -1 : 1;
            float x = (x_y) ? (float)rand() / RAND_MAX * 2 : right_left1;
            float y = (!x_y) ? (float)rand() / RAND_MAX * 2 : right_left2;
            float speed_x = ((float)rand() / RAND_MAX - ((right_left1) ? 1 : 0)) / 100;
            float speed_y = ((float)rand() / RAND_MAX - ((!right_left2) ? 1 : 0)) / 100;
            asteroids.push_back(new asteroid(speed_x, speed_y, x, y, 1, 0, 0));
        }
        for(int i = 0; i < asteroids.size(); i++)
        {
            bool out = asteroids[i]->out_of_bounds(1.2, 1.2);
            asteroids[i]->update(window, window_width, window_height);
            if(out)
            {
                asteroids[i]->destruct();
                delete asteroids[i];
                asteroids.erase(asteroids.begin() + i);
            }
            else
            {
                asteroids[i]->check_all_collisions(space_ship.receive_bullets());
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        input_handler(window, space_ship);

        if(cooldown >= 50)
        {
            shooting = true;
            cooldown = 0;
        }
        cooldown++;
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
