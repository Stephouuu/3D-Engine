// IFT3100H18 ~ phong_330_vs.glsl

#version 330

// attributs de sommet
in vec4 position;
in vec4 normal;

// attributs en sortie
out vec3 viewSpacePosition;
out vec3 viewSpaceNormal;

// attributs uniformes
uniform mat4x4 modelViewMatrix;
uniform mat4x4 projectionMatrix;
uniform mat4x4 model;
uniform bool isDirectional;

void main()
{
  // calculer la matrice normale
  mat4x4 normalMatrix = transpose(inverse(modelViewMatrix));

  // transformation de la normale du sommet dans l'espace de vue
  viewSpaceNormal = vec3(normalMatrix * normal);

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
  // transformation de la position du sommet par les matrices de modèle, vue et projection
	gl_Position = projectionMatrix * modelViewMatrix * model * position;
}

