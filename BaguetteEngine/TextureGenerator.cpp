//
// Created by joffrey on 18-03-08.
//

#include "TextureGenerator.hpp"

ofImage *TextureGenerator::monochrome(int w, int h, int r, int g, int b) {
    ofImage *renderer = new ofImage();

    renderer->clear();

    renderer->allocate(w, h, OF_IMAGE_COLOR);
    unsigned int i = 0;
    while ( i < renderer->getPixels().size() ) {
        renderer->setColor(i, r);
        renderer->setColor(i + 1, g);
        renderer->setColor(i + 2, b);
        i += 3;
    }
    renderer->update();
    return renderer;
}

ofImage *TextureGenerator::perlinNoise(int h, int w, float resolution) {

    ofImage *renderer = new ofImage();

    renderer->clear();
    renderer->allocate(w, h, OF_IMAGE_COLOR);

    for (int y = 0; y < h * 3; y += 1) {
        for (int x = 0; x < w; x += 3) {
            float noise = ofNoise(x * resolution, y * resolution);
            noise = ofClamp(static_cast<float>(noise * 255), 120, 200);
            renderer->setColor(y * w + x, noise);
        }
    }

    renderer->update();

    return renderer;
}
