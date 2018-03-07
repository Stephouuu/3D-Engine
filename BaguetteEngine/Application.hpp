#pragma once

#include "ofMain.h"

#include "Timer.hpp"
#include "WindowRenderer.hpp"
#include "SceneController.hpp"
#include "BaseGui.hpp"

class Application : public ofBaseApp
{
public:
	Application(void);
	~Application(void);

	void setup(void);
	void update(void);
	void draw(void);

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

private:
	Timer timer_;
	WindowRenderer window_;
	SceneController scene_;

	BaseGui gui_;
};
