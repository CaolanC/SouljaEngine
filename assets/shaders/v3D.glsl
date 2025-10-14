#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;
uniform vec3 uCamPos;

out vec3 vWorldPos;
out vec3 vCamPos;
out vec3 vNorm;
 // expect 4 (FLOAT)
void main() {
    vec4 worldPos = uModel * vec4(aPos, 1.0);
    vWorldPos = worldPos.xyz;
    vCamPos   = uCamPos;

    gl_Position = uProjection * uView * worldPos ;
    vNorm = aNorm;
}
