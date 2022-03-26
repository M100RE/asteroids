#include "../../rendering/shape/shape.h"
#include <GLFW/glfw3.h>

class entity
{ 
protected:
    float pos_x;
    float pos_y;
    float speed_x;
    float speed_y;

    shape body;
public:
    entity(float* vertices, int size_vertices, unsigned int* indices, int size_indices, const char* vertex_path, const char* fragment_path);

    void rotate(float degree);
    void move(float x_coord, float y_coord);
    void add_move(float x_direction, float y_direction);
    void add_move_speed();
    void define_speed_x(float speed);
    void define_speed_y(float speed);
    void scale(float scale_x, float scale_y);
    float receive_pos_x() const;
    float receive_pos_y() const;
    virtual void update(GLFWwindow* window, int window_width, int window_height);
};
