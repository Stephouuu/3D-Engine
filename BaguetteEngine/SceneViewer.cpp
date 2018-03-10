#include "SceneViewer.hpp"
#include <sstream>

SceneViewer::SceneViewer(SceneController & scene)
	: scene_(scene)
{
	scene_.setOnGraphSceneChanged(std::bind(&SceneViewer::update, this));
}

SceneViewer::~SceneViewer(void)
{
}

void SceneViewer::draw(void)
{
	gui_.draw();
}

void SceneViewer::setup(void)
{
	layout_.setup();

	update();

	gui_.setup();
	gui_.setName("SceneViewer");
	gui_.setPosition(ofPoint(0, 300));
	gui_.add(&layout_);
}

void SceneViewer::refresh(int newEditorDimension)
{
	(void)newEditorDimension;
}

void SceneViewer::focus(const Identifiable & id)
{
	(void)id;
}

void SceneViewer::windowsResized(const ofPoint & size)
{
	gui_.setPosition(0, size.y / 3.f);
}

void SceneViewer::update(void)
{
	layout_.clear();
	buttons_.clear();

	SceneNode::TreeData data;
	scene_.graphContent(data);

	for (auto & it : data)
	{
		if (it.first > 0)
			buttons_.emplace_back();
	}

	int i = 1;
	for (auto & it : buttons_)
	{
		std::ostringstream oss;

		for (int j = 0; j < data[i].first - 1; ++j) {
			oss << "  ";
		}
		oss << data[i].second.getID() << "-" << data[i].second.getName();
		std::string s = oss.str();

		it.setup(s);
		it.addListener(this, &SceneViewer::buttonPressed);
		layout_.add(&it);

		i++;
	}
}

void SceneViewer::buttonPressed(const void * sender)
{
	ofxButton *button = (ofxButton *)sender;
	std::string name = button->getName();

	size_t start = name.find_first_not_of(' ');
	size_t end = name.find_first_of('-');
	std::string sid = name.substr(start, end - start);

	Identifiable id(std::stoi(sid));
	scene_.setFocusedDrawable(id);
}