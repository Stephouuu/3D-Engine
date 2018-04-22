// IFT3100H18 ~ blinn_phong_330_fs.glsl

#version 330

// attributs interpol�s � partir des valeurs en sortie du shader de sommet
in vec3 viewSpacePosition;
in vec3 viewSpaceNormal;

// attribut en sortie
out vec4 fragmentColor;

// couleurs de r�flexion du mat�riau
uniform int lightNb;

uniform vec3 colorAmbient0;
uniform vec3 colorDiffuse0;
uniform vec3 colorSpecular0;

uniform vec3 colorAmbient1;
uniform vec3 colorDiffuse1;
uniform vec3 colorSpecular1;

uniform vec3 colorAmbient2;
uniform vec3 colorDiffuse2;
uniform vec3 colorSpecular2;

uniform vec3 colorAmbient3;
uniform vec3 colorDiffuse3;
uniform vec3 colorSpecular3;

uniform float coneAngle;

// facteur de brillance sp�culaire du mat�riau
uniform float brightness;

// position d'une source de lumi�re
uniform vec3 lightPosition0;
uniform vec3 lightPosition1;
uniform vec3 lightPosition2;
uniform vec3 lightPosition3;

void main()
{
  // re-normaliser la normale apr�s interpolation
  vec3 N = normalize(viewSpaceNormal);


  if (lightNb > 0)
  {
    // calculer la direction de la surface vers la lumi�re (L)
  vec3 L = normalize(lightPosition0 - viewSpacePosition);

   float attenuation = 1.0;

  if (coneAngle > -1)
  {
	vec3 coneDirection = vec3(0, 0, -1);
	float distanceToLight = length(lightPosition0 - viewSpacePosition);
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
    colorAmbient0 +
	attenuation *
    (colorDiffuse0 * reflectionDiffuse +
    colorSpecular0 * reflectionSpecular), 1.0);
  }
  if (lightNb > 1)
  {
      // calculer la direction de la surface vers la lumi�re (L)
  vec3 L = normalize(lightPosition1 - viewSpacePosition);

   float attenuation = 1.0;

  if (coneAngle > -1)
  {
	vec3 coneDirection = vec3(0, 0, -1);
	float distanceToLight = length(lightPosition1 - viewSpacePosition);
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
  fragmentColor += vec4(
    colorAmbient1 +
	attenuation *
    (colorDiffuse1 * reflectionDiffuse +
    colorSpecular1 * reflectionSpecular), 1.0);
  }
  if (lightNb > 2)
  {
      // calculer la direction de la surface vers la lumi�re (L)
  vec3 L = normalize(lightPosition2 - viewSpacePosition);

   float attenuation = 1.0;

  if (coneAngle > -1)
  {
	vec3 coneDirection = vec3(0, 0, -1);
	float distanceToLight = length(lightPosition2 - viewSpacePosition);
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
  fragmentColor += vec4(
    colorAmbient2 +
	attenuation *
    (colorDiffuse2 * reflectionDiffuse +
    colorSpecular2 * reflectionSpecular), 1.0);
  }
  if (lightNb > 3)
  {
      // calculer la direction de la surface vers la lumi�re (L)
  vec3 L = normalize(lightPosition3 - viewSpacePosition);

   float attenuation = 1.0;

  if (coneAngle > -1)
  {
	vec3 coneDirection = vec3(0, 0, -1);
	float distanceToLight = length(lightPosition3 - viewSpacePosition);
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
  fragmentColor += vec4(
    colorAmbient3 +
	attenuation *
    (colorDiffuse3 * reflectionDiffuse +
    colorSpecular3 * reflectionSpecular), 1.0);
  }

}