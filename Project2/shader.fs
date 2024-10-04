#version 330 core
in vec3 ourColor;  // Input from the vertex shader

out vec4 FragColor;
in vec3 ourPosition;

void main() {
    FragColor = vec4(ourPosition, 1.0);  // Use the color passed from the vertex shader
}
