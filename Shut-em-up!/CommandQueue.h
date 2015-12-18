#pragma once
#include <queue>
#include "Command.h"

struct CommandQueue
{
	void push(const Command& command);
	Command pop();
	bool isEmpty() const;
	std::queue<Command> queue;
};

