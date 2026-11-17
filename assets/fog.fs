#version 330
in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragWorldPos;
uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform vec3 viewPos;
uniform vec3 fogColor;
uniform float fogStart;
uniform float fogEnd;
out vec4 finalColor;

void main(){
    vec4 color = texture(texture0, fragTexCoord) * colDiffuse * fragColor;
    float distanceToCamera = lenght(fragWorldPos - viewPos);
    float fogAmount = clamp((distanceToCamera - fogStart) / (fogEnd - fogStart), 0.0, 1.0);
    finalColor = vec4(mix(color.rgb, fogColor, fogAmount), 1.0);
}