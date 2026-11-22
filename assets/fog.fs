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

    // float gray = dot(color.rgb, vec3(0.299, 0.587, 0.114));
    // color.rgb = mix(vec3(gray), color.rgb, 0.25);

    float distanceToCamera = length(fragWorldPos - viewPos);
    float cal = clamp((distanceToCamera - fogStart) / (fogEnd - fogStart), 0.0, 1.0);
    float fogAmount = cal * cal * (3.0 - 2.0 * cal);

    vec3 toFragment= normalize(fragWorldPos - viewPos);
    vec3 direction = normalize(viewDir);

    float facing = dot(toFragment);
    float visibity = smoothstep(coneOuter, coneInner, facing);
    float directionDark = 1.0 - visibity;
    float dark = max(cal, directionDark * 0.96);

    finalColor = vec4(mix(color.rgb, fogColor, dark), color.a);
}