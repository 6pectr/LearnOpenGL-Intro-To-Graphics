#version 330 core
layout(location = 0) in vec3 aPos; // Vertex position
layout(location = 1) in vec3 aColor; // Vertex color

uniform float u_offset_x; // Player's x position
uniform float u_offset_y; // Player's y position
uniform float u_scale; // Scale factor

void main() {
    gl_Position = vec4((aPos.x * u_scale) + u_offset_x, (aPos.y * u_scale) + u_offset_y, aPos.z, 1.0);
}
