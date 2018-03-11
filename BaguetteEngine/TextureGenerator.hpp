//
// Created by joffrey on 18-03-08.
//

#pragma once

#include "ofMain.h"

class TextureGenerator {
public:
    static ofImage *monochrome(int x, int y, int r, int g, int b);
    static ofImage *perlinNoise(int x, int y, float resolution);
};
