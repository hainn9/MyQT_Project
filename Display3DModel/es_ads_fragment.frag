#define FP highp

uniform FP vec4 lightPosition;
uniform FP vec3 lightIntensity;
uniform FP vec3 lightDirection;
uniform FP vec3 qt_EyePosition;

// TODO: Replace with a struct
uniform FP vec3 Ka;            // Ambient reflectivity
//uniform FP vec3 Kd;            // Diffuse reflectivity
//uniform FP vec3 Ks;            // Specular reflectivity
//uniform FP float shininess;    // Specular shininess factor
//uniform FP sampler2D texture;
//uniform FP samplerCube texture;

varying FP vec3 v_position;
varying FP vec3 v_normal;
varying FP vec3 v_texcoord;
//varying FP vec2 v_texcd;

const float c_zero = 0.0;
const float c_one = 1.0;
//FP vec4 evaluateColor(const FP vec3 normal, const FP vec3 texCoord)
//{
//    FP vec3 finalColor = vec3(c_zero, c_zero, c_zero);
//    //Ambient component
//    finalColor += Ka;
//    //Diffuse component
//    FP vec3 lightDir = normalize(lightDirection);
//    FP float diffuseFactor = max(c_zero, dot(lightDir, normal));
//    if(diffuseFactor > c_zero)
//    {
//        finalColor += Kd * diffuseFactor;
//    }
//    //Specular component
//    FP vec3 viewDir = normalize(qt_EyePosition - v_position);
//    FP vec3 reflectionVec = reflect(viewDir, normal);
//    const vec3 blackColor = vec3(c_zero, c_zero, c_zero);
//    if( !(Ks == blackColor || shininess == c_zero) )
//    {
//        FP float specularFactor = max( c_zero, dot(reflectionVec, -viewDir) );
//        if(specularFactor > c_zero)
//        {
//            specularFactor = pow( specularFactor, shininess );
//            finalColor += Ks * specularFactor;
//        }
//    }

//    finalColor *= textureCube(texture, reflectionVec).rgb;
//    return /*lightIntensity**/vec4( finalColor, c_one );
//}

FP vec3 adsModel( const FP vec3 pos, const FP vec3 n )
{
    // Calculate the vector from the light to the fragment
    FP vec3 s = normalize( vec3( lightPosition ) - pos );

    // Calculate the vector from the fragment to the eye position
    // (origin since this is in "eye" or "camera" space)
    FP vec3 v = normalize( -pos );

    // Reflect the light beam using the normal at this fragment
    FP vec3 r = reflect( -s, n );

//    FP vec4 texel = textureCube(texture, r);

    // Calculate the diffuse component
    FP float diffuse = max( dot( s, n ), 0.0 );
//    FP vec4 texel = textureCube(texture, v_texcoord);
//    FP vec4 texel = texture2D(texture, v_texcd);
//    FP vec3 KdColor = texel.rgb;

    // Calculate the specular component
    FP float specular = 0.0;
    if ( dot( s, n ) > 0.0 )
        specular = pow( max( dot( r, v ), 0.0 ), shininess );

    // Combine the ambient, diffuse and specular contributions
//    return lightIntensity * ( Ka + KdColor * diffuse + Ks * specular );
    //Full ambient, diffuse, specular of material
//    return lightIntensity * ( Ka + Kd * diffuse + Ks * specular );
    //Only ambient
    return lightIntensity * Ka;
}

void main()
{
    gl_FragColor = vec4( adsModel( v_position, normalize( v_normal ) ), 1.0 )/**textureCube(texture, v_texcoord)*/;
//    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
