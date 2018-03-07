#pragma once
#include <string>
#include<iostream>
#include <ofImage.h>

class Image
{
public:
	Image(std::string filename);
	Image();
	~Image();
	void Load(std::string filename);
	void Export(std::string filename);
	void Draw(float x, float y);
	void Draw(float x, float y, int width, int heigh);
	void DrawPartOfImage(float posx, float posy, float toxpx, float toypx, float fromxpx, float fromypx);

	ofImage theImg;
	std::string name;
	std::string path;
	bool isLoaded;

};

