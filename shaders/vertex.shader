#version 330 core

layout (location = 0) in vec2 pos;

uniform float rotation;
uniform vec2 offset;
uniform vec2 scale;

void main()
{
    float radius = sqrt(pos.x * pos.x + pos.y * pos.y);
    float current_rotation = ((atan(pos.y / pos.x) + ((pos.x >= 0) ? 0 : 3.14159265))) * (180 / 3.14159265);
    float rotation_degree = (current_rotation + rotation) * (3.14159265 / 180);

    gl_Position = vec4((radius * cos(rotation_degree) + offset.x) * scale.x, (radius * sin(rotation_degree) + offset.y) * scale.y, 0.0, 1.0);
}
