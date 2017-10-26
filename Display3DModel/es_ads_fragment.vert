attribute vec3 vertexPosition;
attribute vec3 vertexNormal;
//attribute vec3 a_texcoord;
//attribute vec2 a_texcoord;

varying vec3 v_position;
varying vec3 v_normal;
varying vec3 v_texcoord;
//varying vec2 v_texcd;


uniform mat4 MV;
uniform mat3 N;
uniform mat4 MVP;

void main()
{
    v_normal = normalize( N * vertexNormal );
    v_position = vec3( MV * vec4( vertexPosition, 1.0 ) );
    v_texcoord = vertexPosition.xyz;
//    v_texcoord = v_normal;
//    v_texcoord = vertexPosition + vertexNormal;
//    v_texcoord = vec3(a_texcoord, 0.0);
//    v_texcd = a_texcoord;

    gl_Position = MVP * vec4( vertexPosition, 1.0 );
}
