#version 330
in vec2 fragTexCoord;
in vec3 fragWorldPos;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec3 viewPos;
uniform vec3 viewDir;
uniform vec3 fogColor;
uniform vec4 colDiffuse;
uniform float fogStart;
uniform float fogEnd;
uniform float coneInner;
uniform float coneOuter;

out vec4 finalColor;

void main(){
    vec4 color = texture(texture0, fragTexCoord) * colDiffuse * fragColor;

    float distanceToCamera = length(fragWorldPos - viewPos);
    float cal = clamp((distanceToCamera - fogStart) / (fogEnd - fogStart), 0.0, 1.0);
    float fogAmount = cal * cal * (3.0 - 2.0 * cal);

    vec2 toFragment= fragWorldPos.xz - viewPos.xz;
    vec2 direction = viewDir.xz;

    float fragmentL = length(toFragment);
    float directionL = length(direction);

    float facing = 1.0;

    if(fragmentL > 0.001 && directionL > 0.001){
        toFragment = normalize(toFragment);
        direction = normalize(direction);
        facing = dot(toFragment, direction);
    }

    float visibity = smoothstep(coneOuter, coneInner, facing);
    float directionDark = (1.0 - visibity) * 0.96;

    float darkness = max(fogAmount, directionDark);

    finalColor = vec4(mix(color.rgb, fogColor, darkness), color.a);
}