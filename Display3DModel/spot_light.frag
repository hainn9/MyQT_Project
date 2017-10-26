#define FP highp
//struct spot_light {
//    vec3 position;
//    vec3 ambient;
//    vec3 diffuse;
//    vec3 specular;
//    vec3 spot_direction;
//    float spot_cutoff;
//    float spot_exponent;
//};

//uniform FP spot_light light;

//// TODO: Replace with a struct
//uniform FP vec3 Ka;            // Ambient reflectivity
//uniform FP vec3 Kd;            // Diffuse reflectivity
//uniform FP vec3 Ks;            // Specular reflectivity
//uniform FP float shininess;    // Specular shininess factor

//varying FP vec3 v_position;
//varying FP vec3 v_normal;
//varying FP vec3 v_texcoord;

//const float c_zero = 0.0;
//const float c_one = 1.0;

//FP vec4 spot_light_color(const FP vec3 normal, const FP vec3 position)
//{
//    FP vec3 final_color = vec3(c_zero, c_zero, c_zero);
//    FP vec3 lightDir = light.position - position;
//    lightDir = normalize(lightDir);
//    FP float att_factor = c_one;
//    if (light.spot_cutoff < 180.0)
//    {
//        FP float spot_factor = dot(-lightDir, light.spot_direction);
//        if(spot_factor >= cos(radians(light.spot_cutoff)))
//            spot_factor = pow(spot_factor, light.spot_exponent);
//        else
//            spot_factor = c_zero;
//        att_factor *= spot_factor;
//    }
//    if (att_factor > c_zero)
//    {
//        //ambient component
//        final_color += light.ambient * Ka;
//        //diffusu component
//        FP float diffuseFactor = max(c_zero, dot(lightDir,normal));
//        if (diffuseFactor > c_zero)
//        {
//            final_color += diffuseFactor * light.diffuse * Kd;
//        }
//        //specular component
//        FP vec3 halfplane = normalize(lightDir + vec3(c_zero, c_zero, c_one));
//        FP float specularFactor = dot(normal, halfplane);
//        if (specularFactor > c_zero)
//        {
//            final_color += specularFactor * light.specular * Ks;
//        }
//        final_color *= att_factor;
//    }
//    return vec4(final_color, c_one);
//}

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

uniform FP light u_light;

varying FP vec3 v_normal;
varying FP vec3 v_view;
varying FP vec3 v_dirAniso;
varying FP vec3 v_light;

void StrandLight(vec3 normal, vec3 light, vec3 view, vec3 dirAniso, out float diffuse, out float specular)
{
   float  LdA        = dot( light, dirAniso );
   float  VdA        = dot( view, dirAniso );
   vec2   fnLookup   = texture2D( u_Texture1, vec2( LdA, VdA ) * 0.5 + vec2(0.5,0.5) ).xy;
   float  selfShadow = clamp( dot( normal, light ), 0.0, 1.0 );
   specular          = fnLookup.y * fnLookup.y * selfShadow;
   diffuse           = fnLookup.x * selfShadow;
}

FP vec4 SpotLight(const FP vec3 normal, const FP vec3 light, const FP vec3 view, const FP vec3 dirAniso)
{
   FP vec4 color = vec4(0.0); // light color accumulator
   FP float attenuation = 1.0;
   FP float spotAttenuation;
   FP float d = length(light); // light distance
   FP vec3 dirLight = normalize(light); // direction from light position
   FP vec3 dirSpotlight = u_light.direction; // direction of spot light
   FP float spotDot = dot(dirLight, dirSpotlight);
   FP float strandDiffuse; //will hold diffuse anisotropic lighting
   FP float strandSpecular; //will hold specular anisotropic lighting

   // Out of range or outside of cone: no light.
   if (d > u_light.range || spotDot < u_light.spotCosCutoff) {
      return color;
   }

   // Compute attenuation only if enabled (attenuation.w == 1.0)
   if( u_light.attenuation.w == 1.0 ) {
      attenuation = 1.0 / (u_light.attenuation.x + u_light.attenuation.y * d + u_light.attenuation.z * d * d);
   }

   // Combine the spotlight and distance attenuation.
   spotAttenuation = pow(spotDot, u_light.spotExponent);
   attenuation *= spotAttenuation;

   StrandLight(normal, dirSpotlight, view, dirAniso, strandDiffuse, strandSpecular);
   color += strandDiffuse * u_light.diffuse * attenuation;
   color += strandSpecular * u_light.specular * attenuation;
   color += u_light.ambient * attenuation;

   return color;
}

void main()
{
    vec4 color = vec4(0.0);

    gl_FragColor = spot_light_color(v_normal, v_position);
}
