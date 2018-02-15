#pragma once

#include <chrono>

class Timer
{
public:
	Timer(void);
	~Timer(void);

	/* in milliseconds */
	double restart(void);

	void toggle(void);
	void start(void);
	void pause(void);

	double getElapsedTime(void);

private:
	std::chrono::steady_clock::time_point begin_;
	std::chrono::steady_clock::time_point current_;
	bool running_;
	double value_;
};
