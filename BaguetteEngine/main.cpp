#include "Application.hpp"

int main(void)
{
	ofSetupOpenGL(1024, 768, OF_WINDOW);	
	ofRunApp(new Application);
	return 0;
}
