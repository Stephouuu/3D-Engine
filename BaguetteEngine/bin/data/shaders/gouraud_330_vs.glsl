// IFT3100H18 ~ gouraud_330_vs.glsl

#version 330

// attributs de sommet
in vec4 position;
in vec4 normal;

// attributs en sortie
out vec3 interpolationColor;

// attributs uniformes
uniform mat4x4 modelViewMatrix;
uniform mat4x4 projectionMatrix;
uniform mat4x4 model;
uniform bool isDirectional;

// couleurs de réflexion du matériau
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

// facteur de brillance spéculaire du matériau
uniform float brightness;

// position d'une source de lumière
uniform vec3 lightPosition0;
uniform vec3 lightPosition1;
uniform vec3 lightPosition2;
uniform vec3 lightPosition3;

void main()
{
  // calculer la matrice normale
  mat4x4 normalMatrix = transpose(inverse(modelViewMatrix));

  // transformation de la normale du sommet dans l'espace de vue
  vec3 viewSpaceNormal = vec3(normalMatrix * normal);

  vec3 viewSpacePosition = vec3(0.0, 0.0 ,0.0);

  if (!isDirectional)
  {
	  // transformation de la position du sommet dans l'espace de vue
	viewSpacePosition = vec3(modelViewMatrix * model * position);
  }
  else
  {
	  // transformation de la position du sommet dans l'espace de vue
	viewSpacePosition = vec3(modelViewMatrix * position);
  }

  // re-normaliser la normale
  vec3 N = normalize(viewSpaceNormal);


  if (lightNb > 0)
  {
	  // calculer la direction de la surface vers la lumière (L)
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

  // calculer le niveau de réflexion diffuse (N • L)
  float reflectionDiffuse = max(dot(N, L), 0.0);

  // réflexion spéculaire par défaut
  float reflectionSpecular = 0.0;

  // calculer la réflexion spéculaire seulement s'il y a réflexion diffuse
  if (reflectionDiffuse > 0.0)
  {
    // calculer la direction de la surface vers la caméra (V)
    vec3 V = normalize(-viewSpacePosition);

    // calculer la direction de la réflection (R) du rayon incident (-L) en fonction de la normale (N)
    vec3 R = reflect(-L, N);

    // calculer le niveau de réflexion spéculaire (R • V)
    reflectionSpecular = pow(max(dot(V, R), 0.0), brightness);
  }

  // calculer la couleur du fragment
  interpolationColor = vec3(
    colorAmbient0 +
	attenuation *
    (colorDiffuse0 * reflectionDiffuse +
    colorSpecular0 * reflectionSpecular));
  }
  if (lightNb > 1)
  {
	  // calculer la direction de la surface vers la lumière (L)
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

  // calculer le niveau de réflexion diffuse (N • L)
  float reflectionDiffuse = max(dot(N, L), 0.0);

  // réflexion spéculaire par défaut
  float reflectionSpecular = 0.0;

  // calculer la réflexion spéculaire seulement s'il y a réflexion diffuse
  if (reflectionDiffuse > 0.0)
  {
    // calculer la direction de la surface vers la caméra (V)
    vec3 V = normalize(-viewSpacePosition);

    // calculer la direction de la réflection (R) du rayon incident (-L) en fonction de la normale (N)
    vec3 R = reflect(-L, N);

    // calculer le niveau de réflexion spéculaire (R • V)
    reflectionSpecular = pow(max(dot(V, R), 0.0), brightness);
  }

  // calculer la couleur du fragment
  interpolationColor += vec3(
    colorAmbient1 +
	attenuation *
    (colorDiffuse1 * reflectionDiffuse +
    colorSpecular1 * reflectionSpecular));
  }
  if (lightNb > 2)
  {
    // calculer la direction de la surface vers la lumière (L)
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

  // calculer le niveau de réflexion diffuse (N • L)
  float reflectionDiffuse = max(dot(N, L), 0.0);

  // réflexion spéculaire par défaut
  float reflectionSpecular = 0.0;

  // calculer la réflexion spéculaire seulement s'il y a réflexion diffuse
  if (reflectionDiffuse > 0.0)
  {
    // calculer la direction de la surface vers la caméra (V)
    vec3 V = normalize(-viewSpacePosition);

    // calculer la direction de la réflection (R) du rayon incident (-L) en fonction de la normale (N)
    vec3 R = reflect(-L, N);

    // calculer le niveau de réflexion spéculaire (R • V)
    reflectionSpecular = pow(max(dot(V, R), 0.0), brightness);
  }

  // calculer la couleur du fragment
  interpolationColor += vec3(
    colorAmbient2 +
	attenuation *
    (colorDiffuse2 * reflectionDiffuse +
    colorSpecular2 * reflectionSpecular));
  }
  if (lightNb > 3)
  {
    // calculer la direction de la surface vers la lumière (L)
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

  // calculer le niveau de réflexion diffuse (N • L)
  float reflectionDiffuse = max(dot(N, L), 0.0);

  // réflexion spéculaire par défaut
  float reflectionSpecular = 0.0;

  // calculer la réflexion spéculaire seulement s'il y a réflexion diffuse
  if (reflectionDiffuse > 0.0)
  {
    // calculer la direction de la surface vers la caméra (V)
    vec3 V = normalize(-viewSpacePosition);

    // calculer la direction de la réflection (R) du rayon incident (-L) en fonction de la normale (N)
    vec3 R = reflect(-L, N);

    // calculer le niveau de réflexion spéculaire (R • V)
    reflectionSpecular = pow(max(dot(V, R), 0.0), brightness);
  }

  // calculer la couleur du fragment
  interpolationColor += vec3(
    colorAmbient3 +
	attenuation *
    (colorDiffuse3 * reflectionDiffuse +
    colorSpecular3 * reflectionSpecular));
  }
    // transformation de la position du sommet par les matrices de modèle, vue et projection
	 gl_Position = projectionMatrix * modelViewMatrix * model * position;
}
