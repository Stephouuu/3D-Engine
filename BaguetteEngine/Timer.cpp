#include "Timer.hpp"

Timer::Timer(void)
{
  running_ = false;
  value_ = 0;
}

Timer::~Timer(void)
{
}

double Timer::restart(void)
{
	double elapsed = 0.;

	elapsed = getElapsedTime();
	value_ = 0.;
	start();
	return (elapsed);
}

void Timer::toggle(void)
{
  if (!running_)
    start();
  else
    pause();
}

void Timer::start(void)
{
  current_ = std::chrono::steady_clock::now();
  if (!running_)
    running_ = true;
}

void Timer::pause(void)
{
  if (running_)
    {
      value_ += getElapsedTime();
      running_ = false;
    }
}

double Timer::getElapsedTime(void)
{
  if (running_)
    {
      begin_ = std::chrono::steady_clock::now();
      std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double> >(begin_ - current_);
      return (time_span.count() + value_);
    }
  return (value_);
}
