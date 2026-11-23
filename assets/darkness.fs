#version 330

in vec2 fragTexCoord;
out vec4 finalColor;

uniform vec2 resolution;
uniform vec2 center;
uniform float radius;
uniform float softness;
uniform float time;

void main(){
    vec2 uv = fragTexCoord;
    vec2 aspect = vec2(resolution.x / resolution.y, 1.0);
    vec2 p = (uv - center) * aspect;
    float angle = atan(p.y, p.x);

    float irre = sin(angle * 3.0 + time * 0.15) * 0.0025 + sin(angle * 5.0 - time * 0.10) * 0.015;

    float distanceCenter = length(p);
    float edge = radius + irre;

    float visibity = 1.0 - smoothstep(edge - softness, edge, distanceCenter);

    float darkness = 1.0 - visibity;
    finalColor = vec4(0.0, 0.0, 0.0, darkness);
}