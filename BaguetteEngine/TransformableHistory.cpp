#include "TransformableHistory.hpp"
#include <iostream>

TransformableHistory::TransformableHistory(void)
{
	current_ = historic_.cend();
}

TransformableHistory::~TransformableHistory(void)
{
}

void TransformableHistory::deleteTransformations(const Identifiable & id)
{
	std::list<Item>::iterator it = historic_.begin();

	while (it != historic_.end()) {
		if (it->first == id) {
			if (current_->first.getID() == it->first.getID()) {
				if (current_ == --historic_.cend()) {
					--current_;
				}
				else {
					++current_;
				}
			}
			it = historic_.erase(it);
		}
		else {
			++it;
		}
	}
}

void TransformableHistory::pushTransformation(const Item & t)
{
	// current_ = historic_.insert(current_, t);
	historic_.push_front(t);
	current_ = std::begin(historic_);

	std::list<Item>::iterator it = historic_.begin();
	size_t cpt = 0;
	while (it != historic_.end()) {
		if (cpt > MAX_HISTORY - 1) {
			if (current_ == it)
				current_ = --it;
			it = historic_.erase(it);
		}
		else {
			++it;
			++cpt;
		}
	}
}

const TransformableHistory::Item & TransformableHistory::undo(void)
{
	if (current_ != historic_.cend() && current_ != --historic_.cend()) {
		auto tmp = current_;
		current_++;
		if (current_ != historic_.cend()) {
			if (tmp->first.getID() != current_->first.getID()) {
				return *(++current_);
			}
			else {
				return *current_;
			}
		}
	}
	throw std::runtime_error("Nothing to undo.");
}

const TransformableHistory::Item & TransformableHistory::redo(void)
{
	if (current_ != historic_.cbegin()) {
		auto tmp = current_;
		current_--;

		if (current_ != historic_.cbegin() && tmp->first.getID() != current_->first.getID()) {
			return *(--current_);
		}
		else {
			return *current_;
		}
	}
	throw std::runtime_error("Nothing to redo");
}