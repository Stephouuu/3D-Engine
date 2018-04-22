// IFT3100H18 ~ lambert_330_fs.glsl

#version 330

// attributs interpolés à partir des valeurs en sortie du shader de sommets
in vec3 viewSpacePosition;
in vec3 viewSpaceNormal;

// attribut en sortie
out vec4 fragmentColor;

// couleurs de réflexion du matériau
uniform int lightNb;

uniform vec3 colorAmbient0;
uniform vec3 colorDiffuse0;

uniform vec3 colorAmbient1;
uniform vec3 colorDiffuse1;

uniform vec3 colorAmbient2;
uniform vec3 colorDiffuse2;

uniform vec3 colorAmbient3;
uniform vec3 colorDiffuse3;

// position d'une source de lumière
uniform vec3 lightPosition0;
uniform vec3 lightPosition1;
uniform vec3 lightPosition2;
uniform vec3 lightPosition3;

void main()
{
  // re-normaliser la normale après interpolation (N)
  vec3 n = normalize(viewSpaceNormal);

  if (lightNb > 0)
  {
	  // calculer la direction de la surface vers la lumière (L)
  vec3 l = normalize(lightPosition0 - viewSpacePosition);

  // calculer le niveau de réflexion diffuse (N • L)
  float reflection_diffuse = max(dot(n, l), 0.0);

  // déterminer la couleur du fragment
  fragmentColor = vec4(colorAmbient0 + colorDiffuse0 * reflection_diffuse, 1.0);
  }
  if (lightNb > 1)
  {
	  // calculer la direction de la surface vers la lumière (L)
  vec3 l = normalize(lightPosition1 - viewSpacePosition);

  // calculer le niveau de réflexion diffuse (N • L)
  float reflection_diffuse = max(dot(n, l), 0.0);

  // déterminer la couleur du fragment
  fragmentColor += vec4(colorAmbient1 + colorDiffuse1 * reflection_diffuse, 1.0);
  }
  if (lightNb > 2)
  {
	  // calculer la direction de la surface vers la lumière (L)
  vec3 l = normalize(lightPosition2 - viewSpacePosition);

  // calculer le niveau de réflexion diffuse (N • L)
  float reflection_diffuse = max(dot(n, l), 0.0);

  // déterminer la couleur du fragment
  fragmentColor += vec4(colorAmbient2 + colorDiffuse2 * reflection_diffuse, 1.0);
  }
  if (lightNb > 3)
  {
  // calculer la direction de la surface vers la lumière (L)
  vec3 l = normalize(lightPosition3 - viewSpacePosition);

  // calculer le niveau de réflexion diffuse (N • L)
  float reflection_diffuse = max(dot(n, l), 0.0);

  // déterminer la couleur du fragment
  fragmentColor += vec4(colorAmbient3 + colorDiffuse3 * reflection_diffuse, 1.0);
  }
}
