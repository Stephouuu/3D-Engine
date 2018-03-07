#include "Application.hpp"

int main(void)
{
	ofGLFWWindowSettings windowSettings;
	windowSettings.setGLVersion(3, 3);
	ofCreateWindow(windowSettings);
	ofRunApp(new Application);
	return 0;
}
