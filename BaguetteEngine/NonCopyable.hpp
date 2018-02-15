#pragma once

struct NonCopyable
{
	NonCopyable(void) {}
	~NonCopyable(void) {}
	NonCopyable(const NonCopyable & other) = delete;
	NonCopyable & operator=(const NonCopyable & other) = delete;
};