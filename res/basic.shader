##shader vertex
#version 460 core

layout (location = 0) in vec4 position;

void main()
{
    gl_Position = position;
}

##shader fragment
#version 460 core

out vec4 color;

void main()
{
    color = vec4(0.2, 0.1, 0.3, 1.0);
}
