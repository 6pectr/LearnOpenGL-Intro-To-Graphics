#version 330 core
in vec3 ourColor;  // Input from the vertex shader
//in vec3 aPosss;

out vec4 FragColor;

void main() {
    FragColor = vec4(ourColor, 1.0);  // Use the color passed from the vertex shader
}
