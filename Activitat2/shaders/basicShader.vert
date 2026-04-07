#version 330 core

in vec3 vertex;
in vec3 color;

uniform mat4 TG;
uniform mat4 Proj;
uniform mat4 View;

//Creem una variable uniform
uniform bool pintaVermell;

out vec3 fcolor;

void main() {
    // Si pintaVermell == true, els vertex es pinten de vermell. 
    if(pintaVermell) fcolor = vec3(1.0, 0.0, 0.0);
    else fcolor = color;
    gl_Position = Proj * View * TG * vec4 (vertex, 1.0);
}
