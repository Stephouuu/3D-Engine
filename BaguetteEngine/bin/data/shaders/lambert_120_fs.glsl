// IFT3100H18 ~ lambert_120_fs.glsl

#version 120

// attributs interpolés à partir des valeurs en sortie du shader de sommets
varying vec3 viewSpacePosition;
varying vec3 viewSpaceNormal;

// position d'une source de lumière
uniform int lightNb;

uniform vec3 lightPosition0;
uniform vec3 lightPosition1;
uniform vec3 lightPosition2;
uniform vec3 lightPosition3;

// couleurs de réflexion du matériau
uniform vec3 colorAmbient0;
uniform vec3 colorDiffuse0;

uniform vec3 colorAmbient1;
uniform vec3 colorDiffuse1;

uniform vec3 colorAmbient2;
uniform vec3 colorDiffuse2;

uniform vec3 colorAmbient3;
uniform vec3 colorDiffuse3;

void main()
{
  // re-normaliser la normale après interpolation (N)
  vec3 n = normalize(viewSpaceNormal);

  if (lightNb > 0)
  {
    // calculer la direction de la surface vers la lumière (L)
	vec3 l = normalize(lightPosition - viewSpacePosition);

	// calculer le niveau de réflexion diffuse (N • L)
	float reflection_diffuse = max(dot(n, l), 0.0);

	// déterminer la couleur du fragment
	gl_FragColor = vec4(colorAmbient + colorDiffuse * reflection_diffuse, 1.0);
  }
  if (lightNb > 1)
  {
      // calculer la direction de la surface vers la lumière (L)
	vec3 l = normalize(lightPosition - viewSpacePosition);

	// calculer le niveau de réflexion diffuse (N • L)
	float reflection_diffuse = max(dot(n, l), 0.0);

	// déterminer la couleur du fragment
	gl_FragColor = vec4(colorAmbient + colorDiffuse * reflection_diffuse, 1.0);
  }
  if (lightNb > 2)
  {
      // calculer la direction de la surface vers la lumière (L)
	vec3 l = normalize(lightPosition - viewSpacePosition);

	// calculer le niveau de réflexion diffuse (N • L)
	float reflection_diffuse = max(dot(n, l), 0.0);

	// déterminer la couleur du fragment
	gl_FragColor = vec4(colorAmbient + colorDiffuse * reflection_diffuse, 1.0);
  }
  if (lightNb > 3)
  {
        // calculer la direction de la surface vers la lumière (L)
	vec3 l = normalize(lightPosition - viewSpacePosition);

	// calculer le niveau de réflexion diffuse (N • L)
	float reflection_diffuse = max(dot(n, l), 0.0);

	// déterminer la couleur du fragment
	gl_FragColor = vec4(colorAmbient + colorDiffuse * reflection_diffuse, 1.0);	
  }
}
