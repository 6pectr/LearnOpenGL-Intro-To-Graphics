#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;  // Output to the fragment shader
out vec3 ourPosition;

uniform float u_offset;

void main() {
    gl_Position = vec4(u_offset + aPos.x, -aPos.y, aPos.z, 1.0); 
    ourPosition = aPos;  // Pass the color to the fragment shader
}
