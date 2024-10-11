#version 330 core
layout(location = 0) in vec3 aPos; // Vertex position
layout(location = 1) in vec3 aColor; // Vertex color

out vec3 ourColor;
//out vec3 aPosss;
uniform float u_offset;


void main() {
    gl_Position = vec4(aPos.x, aPos.y + u_offset, aPos.z, 1.0);
    ourColor =  aColor;
    //aPosss = aPos;
}
