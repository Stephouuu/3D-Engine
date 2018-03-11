#include "Image.h"
#include "ofMain.h"
#include <commdlg.h>
#include <ctime>
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

void Image::Load()
{
	ofFileDialogResult result = ofSystemLoadDialog("Load file");
	if (result.bSuccess) {
		path = result.getPath();
		name = result.getName();
		// load your file at `path`
		theImg.load(path);
		isLoaded = true;
	}
}

void Image::LoadCrop(int x, int y, int w, int h)
{
	ofFileDialogResult result = ofSystemLoadDialog("Load file");
	if (result.bSuccess) {
		path = result.getPath();
		name = "cropped-"+result.getName();
		// load your file at `path`
		theImg.load(path);
		theImg.crop(x, y, w, h);
		isLoaded = true;
	}

}

void Image::Export(std::string filename)
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, sizeof(buffer), "%d%m%Y%I%M%S", timeinfo);
	std::string str(buffer);
	theImg.grabScreen(0,0,ofGetWidth(), ofGetHeight());
	theImg.save("Image/"+filename+str+".jpg");
}

void Image::Draw(float x, float y)
{
	if (isLoaded)
		theImg.draw(x, y);
	else
		std::cerr << "No image loaded" << std::endl;
}
void Image::Draw(float x, float y, int width, int heigh)
{
	if (isLoaded)
		theImg.draw(x, y,width, heigh);
	else
		std::cerr << "No image loaded" << std::endl;
}

void Image::DrawPartOfImage(float posx, float posy, float toxpx, float toypx, float fromxpx, float fromypx)
{
	if (isLoaded)
	{
		theImg.drawSubsection(posx, posy, toxpx, toypx, fromxpx, fromypx);
	}
	else
		std::cerr << "No image loaded" << std::endl;
}