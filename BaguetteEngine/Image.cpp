#include "Image.hpp"
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
		std::size_t pos = result.getName().find(".");
		std::string extension = result.getName().substr(pos + 1);
		std::cout << extension << std::endl;
		if (extension == "png" || extension == "jpg" || extension == "gif" || extension == "bmp")
		{
			path = result.getPath();
			name = result.getName();
			// load your file at `path`
			theImg.load(path);
			isLoaded = true;
		}
		else
			std::cerr<< "Error : It's not an Image"<<std::endl;
	}
}

void Image::LoadCrop(int x, int y, int w, int h)
{
	ofFileDialogResult result = ofSystemLoadDialog("Load file");
	if (result.bSuccess) {
		std::size_t pos = result.getName().find(".");
		std::string extension = result.getName().substr(pos + 1);
		if (extension == "png" || extension == "jpg" || extension == "gif" || extension == "bmp")
		{
			path = result.getPath();
			name = "cropped-" + result.getName();
			// load your file at `path`
			theImg.load(path);
			if ((x <= theImg.getWidth()) && (y <= theImg.getHeight()) && (w <= (theImg.getWidth() - x)) && (h <= (theImg.getHeight() - y)))
				theImg.crop(x, y, w, h);
			else
			{
				std::cerr << "Erreur dans vos dimensions, faites attention a la resolution de votre image" << std::endl;
			}
			isLoaded = true;
		}
		else
			std::cerr << "Error : It's not an Image" << std::endl;

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