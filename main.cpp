#include <iostream>

#include <glad/glad.h>
#include "entities/player/player.h"

int window_height = 800;
int window_width = 800;

bool shooting = true;
int cooldown = 0;

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

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        space_ship.update(window, window_width, window_height);

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
