#ifndef _SHAPE_H
#define _SHAPE_H

#include "buffers/vbo.h"
#include "buffers/vao.h"
#include "shader/shader.h"
#include "buffers/ebo.h"

class shape
{
private:
    VAO vao;
    VBO vbo;
    EBO ebo;
    shader_program program;
    bool elements;
    int size;
public:
    shape(const void* vertices, const int vertices_size, const void* indices, const int indices_size, const char* vertex_path, const char* fragment_path);
    void draw();
    shader_program receive_shader();
};

#endif
