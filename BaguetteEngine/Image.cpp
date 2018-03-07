#include "Image.h"
#include "ofMain.h"
#include <commdlg.h>

Image::Image()
{
	isLoaded = false;
}

Image::Image(std::string filename)
{
	if (theImg.load("Image/" + filename) == 0)
		throw std::invalid_argument("Wrong Path.");
	else
		isLoaded = true;
}


Image::~Image()
{
}

void Image::Load(std::string filename)
{
	ofFileDialogResult result = ofSystemLoadDialog("Load file");
	if (result.bSuccess) {
		string path = result.getPath();
		name = result.getName;
		// load your file at `path`
		theImg.load(path);
		isLoaded = true;
	}
}

void Image::Export(std::string filename)
{
	theImg.grabScreen(0,0,ofGetWidth(), ofGetHeight());
	theImg.save("Image/"+filename + ".jpg");
}

void Image::Draw(float x, float y)
{
	if (isLoaded)
		theImg.draw(x, y);
	else
		throw std::invalid_argument("No images Loaded.");
}
void Image::Draw(float x, float y, int width, int heigh)
{
	if (isLoaded)
		theImg.draw(x, y,width, heigh);
	else
		throw std::invalid_argument("No images Loaded.");
}

void Image::DrawPartOfImage(float posx, float posy, float toxpx, float toypx, float fromxpx, float fromypx)
{
	if (isLoaded)
		theImg.drawSubsection(posx, posy, toxpx, toypx, fromxpx, fromypx);
	else
		throw std::invalid_argument("No images Loaded.");
}