##shader vertex
#version 460 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 v_Pos;
out vec3 v_normal;
out vec2 v_texCoords;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    v_normal = normalize((u_model * vec4(normal, 0.0)).xyz);
    gl_Position = u_projection * u_view * u_model * position;
    v_texCoords = texCoords;
    vec4 pos = u_view * u_model * position;
    v_Pos = pos.xyz/pos.w;
}

##shader fragment
#version 460 core

out vec4 color;

in vec3 v_Pos;
in vec3 v_normal;
in vec2 v_texCoords;

uniform sampler2D u_texture;
uniform sampler2D u_skybox;

void main()
{
    vec3 lightDir = normalize(vec3(0.0, 1.0, 0.0));
    vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);

    vec4 objectColor = texture(u_texture, v_texCoords);

    float ambientStrength = 0.1;
    vec4 ambient = ambientStrength * lightColor;

    float diff = max(dot(v_normal, lightDir), 0.0);
    vec4 diffuse = diff * lightColor;

    vec3 reflectDir = reflect(-lightDir, v_normal);
    float spec = pow(max(dot(-normalize(v_Pos), reflectDir), 0.0), 32);
    float specularStrength = 1;
    vec4 specular = specularStrength * spec * lightColor;

    color = (ambient + diffuse + specular) * objectColor;
}
