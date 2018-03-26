#include "CameraController.hpp"

CameraController::CameraController(void)
{
	addCamera();
}

CameraController::~CameraController(void)
{
}

void CameraController::reset(void)
{
	if (focused_ != std::cend(cams_)) {
		focused_->second->reset();
	}
}

void CameraController::windowsResized(const ofPoint & newDimension)
{
	updateCamerasLayout();
}

void CameraController::onClick(const ofPoint & position)
{
	unsigned int i = 0;

	for (const auto & it : cams_) {
		int x = (i % 2) * (ofGetWidth() / 2);
		int y = (i / 2) * (ofGetHeight() / 2);

		if (cams_.size() == 2) {
			if (position.x > x && position.x < x + ofGetWidth() / 2 &&
				position.y > y && position.y < y + ofGetHeight()) {
				focused_ = std::cbegin(cams_) + i;
				break;
			}
		}
		else if (cams_.size() == 3) {
			if ((position.x > x && position.x < x + ofGetWidth() / 2 &&
				position.y > y && position.y < y + ofGetHeight() / 2) || i == 2) {
				focused_ = std::cbegin(cams_) + i;
				break;
			}
		}
		else if (cams_.size() == 4) {
			if (position.x > x && position.x < (i + 1) * x + ofGetWidth() / 2 &&
				position.y > y && position.y < (i + 1) * y + ofGetHeight() / 2) {
				focused_ = std::cbegin(cams_) + i;
				break;
			}
		}
		i++;
	}
}

void CameraController::addCamera(void)
{
	if (cams_.size() < 4) {
		focused_ = cams_.emplace(std::cend(cams_), std::make_pair(ofFbo(), new EasyCamera));
		updateCamerasLayout();
	}
}

void CameraController::removeCamera(void)
{
	if (cams_.size() > 1) {
		if (focused_ != std::cend(cams_)) {
			delete focused_->second;
			cams_.erase(focused_);
			focused_ = std::cbegin(cams_);
		}
		updateCamerasLayout();
	}
}

void CameraController::render(ARenderer & renderer, SceneGraph & scene)
{
	unsigned int i = 0;

	ofClear(255, 255, 255, 255);
	for (const auto & it : cams_) {
		it.first.begin();
			ofClear(ofGetBackgroundColor());
			it.second->begin();
				ofDrawGrid(1, 8U, false, false, true, false);
				scene.render(renderer);
			it.second->end();
		it.first.end();
		it.first.draw(
			(i%2)*(ofGetWidth()/2) + (!(i%2) ? 0 : (cams_.size() == 3 && i == 2) ? 0 : std::min<int>(i, 1)),
			(i/2)*(ofGetHeight()/2) + ((cams_.size() == 3 && i == 2) ? 1 : (cams_.size() != 3) ? 2 : 0)
		);
		++i;
	}
}

void CameraController::update(float dt)
{
	for (const auto & it : cams_) {
		it.second->update(dt);
	}
}

void CameraController::setTarget(const ofVec3f & position)
{
	if (focused_ != std::cend(cams_)) {
		focused_->second->setTarget(position);
	}
}

void CameraController::zoom(int factor)
{
	if (focused_ != std::cend(cams_)) {
		focused_->second->zoom(factor);
	}
}

void CameraController::stop(void)
{
	if (focused_ != std::cend(cams_)) {
		focused_->second->setLongitudeDirection(EasyCamera::OrbitDirection::None);
	}
}

void CameraController::right(void)
{
	if (focused_ != std::cend(cams_)) {
		focused_->second->setLongitudeDirection(EasyCamera::OrbitDirection::Forward);
	}
}

void CameraController::left(void)
{
	if (focused_ != std::cend(cams_)) {
		focused_->second->setLongitudeDirection(EasyCamera::OrbitDirection::Backward);
	}
}

void CameraController::swapPerspectiveOrtho(bool value)
{
	if (focused_ != std::cend(cams_)) {
		if (value) focused_->second->enableOrtho();
		else focused_->second->disableOrtho();
	}
}

void CameraController::updateCamerasLayout(void)
{
	unsigned int i = 0;
	ofPoint dim;

	for (auto & it : cams_) {
		if (it.first.isAllocated())
			it.first.clear();
		dim = {
			(float)ofGetWidth() / ((cams_.size() == 3 && i == 2) ? 1 : std::min<int>(cams_.size(), 2)),
			(float)ofGetHeight() / ((cams_.size() < 3) ? 1 : 2)
		};
		if (!(cams_.size() == 3 && i == 2) && cams_.size() != 3)
			dim.y -= 1;
		it.first.allocate(dim.x, dim.y);
		++i;
	}
}