#pragma once
#include <string>
#include<iostream>
#include <ofImage.h>

class Image
{
public:
	Image();
	Image(std::string filename);
	~Image();
	void Load();
	void LoadCrop(int x, int y, int w, int h);
	void Export(std::string filename);
	void Draw(float x, float y);
	void Draw(float x, float y, int width, int heigh);
	void DrawPartOfImage(float posx, float posy, float toxpx, float toypx, float fromxpx, float fromypx);

	ofImage theImg;
	string name;
	std::string path;
	bool isLoaded;

};

