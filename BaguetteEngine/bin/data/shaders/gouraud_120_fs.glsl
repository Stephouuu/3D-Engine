// IFT3100H18 ~ gouraud_120_fs.glsl

#version 120

// attribut interpolé à partir des valeurs en sortie du shader de sommet
varying vec3 interpolationColor;

void main()
{
  // calculer la couleur du fragment
  gl_FragColor = vec4(interpolationColor, 1.0);
}
