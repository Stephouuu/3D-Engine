// IFT3100H18 ~ blinn_phong_330_fs.glsl

#version 330

// attributs interpol�s � partir des valeurs en sortie du shader de sommet
in vec3 viewSpacePosition;
in vec3 viewSpaceNormal;

// attribut en sortie
out vec4 fragmentColor;

// couleurs de r�flexion du mat�riau
uniform vec3 colorAmbient;
uniform vec3 colorDiffuse;
uniform vec3 colorSpecular;
uniform float coneAngle;

// facteur de brillance sp�culaire du mat�riau
uniform float brightness;

// position d'une source de lumi�re
uniform vec3 lightPosition;

void main()
{
  // re-normaliser la normale apr�s interpolation
  vec3 N = normalize(viewSpaceNormal);

  // calculer la direction de la surface vers la lumi�re (L)
  vec3 L = normalize(lightPosition - viewSpacePosition);

   float attenuation = 1.0;

  if (coneAngle > -1)
  {
	vec3 coneDirection = vec3(0, 0, -1);
	float distanceToLight = length(lightPosition - viewSpacePosition);
	attenuation = 1.0 / (1.0 + 1.5 * pow(distanceToLight, 2)); //The 1.5 value should be dynamic
	//cone restrictions (affects attenuation)
	float lightToSurfaceAngle = degrees(acos(dot(-L, normalize(coneDirection))));
	if (lightToSurfaceAngle > coneAngle)
	{
		attenuation = 0.0;
	}
  }

  // calculer le niveau de r�flexion diffuse (N � L)
  float reflectionDiffuse = max(dot(N, L), 0.0);

  // r�flexion sp�culaire par d�faut
  float reflectionSpecular = 0.0;

  // calculer la r�flexion sp�culaire seulement s'il y a r�flexion diffuse
  if (reflectionDiffuse > 0.0)
  {
    // calculer la direction de la surface vers la cam�ra (V)
    vec3 V = normalize(-viewSpacePosition);

    // calculer la direction du demi-vecteur de r�flection (H) en fonction du vecteur de vue (V) et de lumi�re (L)
    vec3 H = normalize(V + L);

    // calculer le niveau de r�flexion sp�culaire (N � H)
    reflectionSpecular = pow(max(dot(N, H), 0.0), brightness);
  }

  // calculer la couleur du fragment
  fragmentColor = vec4(
    colorAmbient +
	attenuation *
    (colorDiffuse * reflectionDiffuse +
    colorSpecular * reflectionSpecular), 1.0);
}