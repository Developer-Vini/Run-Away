#version 330
in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragWorldPos;
uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform vec3 viewPos;
out vec4 finalColor;

void main(){

    vec3 albedo = texture(texture0, fragTexCoord).rgb * colDiffuse.rgb;
    vec3 normal = normalize(fragNormal);

    vec3 lihgtDirection = normalize(vec3(0.4, 0.9, -0.4));
    vec3 lColor = vec3(0.55, 0.72, 0.75);
    vec3 ambientColor = vec3(0.05, 0.06, 0.08);


    float diffuse = max(dot(normal, lihgtDirection), 0.0);


    vec3 viewDirection = normalize(viewPos - fragWorldPos);
    vec3 halfDirection = normalize(lihgtDirection + viewDirection);
    float spl = pow(max(dot(normal, halfDirection + viewDirection), 0.0), 32.0) * 35.0;

    vec3 color = albedo * (ambientColor + diffuse * lColor) + spl;
    finalColor = vec4(color, 1.0); 

}