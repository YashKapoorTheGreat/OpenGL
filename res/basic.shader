##shader vertex
#version 460 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
out vec3 v_normal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    v_normal = normalize((u_view * u_model * vec4(normal, 1.0)).xyz);
    gl_Position = u_projection * u_view * u_model * position;
}

##shader fragment
#version 460 core

out vec4 color;
in vec3 v_normal;

void main()
{
    vec4 navyBlue = vec4(0.07, 0.13, 0.17, 1.0);
    vec3 lightDir = normalize(vec3(1.0, 0.0, 1.0));
    vec3 lightDir2 = normalize(vec3(1.0, 0.0, -1.0));
    color = max(dot(v_normal, lightDir), 0.1) * vec4(0.5, 0.8, 1.0, 1.0) +
            max(dot(v_normal, lightDir2), 0.1) * vec4(0.5, 0.8, 1.0, 1.0);
}
