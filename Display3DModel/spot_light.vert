attribute vec3 vertexPosition;
attribute vec3 vertexNormal;
//attribute vec3 a_texcoord;

struct light {
    vec3 position;
    vec3 direction;
    vec3 halplane;
    float spotCosCutoff;
    float spotExponent;
    vec4 attenuation;
    float range;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

uniform mat4 MV;
uniform mat4 M;
uniform vec3 u_camPosition;
uniform mat3 N;
uniform mat4 MVP;
uniform light u_light;

varying vec3 v_normal;
varying vec3 v_dirAniso;  //anisotropy direction
varying vec3 v_view; //camera direction
varying vec3 v_light; //light direction
void main()
{
    vec3 position = (M * vec4(vertexPosition,1.0)).xyz;
    vec3 normal = normalize( N * vertexNormal );

    v_dirAniso = normalize(cross(normal, normalize(position)));
    v_view = normalize(u_camPosition - position);
    v_normal = vertexNormal;
    v_light = u_light.position - vertexPosition;

    gl_Position = MVP * vec4( vertexPosition, 1.0 );
}
