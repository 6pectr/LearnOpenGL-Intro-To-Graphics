#version 330 core
layout(location = 0) in vec3 aPos; // Vertex position
layout(location = 1) in vec3 aColor; // Vertex color
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
//out vec3 aPosss;
uniform float u_offset;
uniform float megaoffset;
out vec2 TexCoord;

void main() {
    gl_Position = vec4(aPos.x, aPos.y + u_offset, aPos.z, 1.0);
    ourColor =  aColor;
    //aPosss = aPos;
    TexCoord = vec2(aTexCoord.x + megaoffset, aTexCoord.y);

}
