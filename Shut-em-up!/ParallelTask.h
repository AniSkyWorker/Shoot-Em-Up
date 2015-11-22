#pragma once
#include "SFML/System.hpp"
struct ParallelTask
{
	ParallelTask();

	void execute();
	bool isFinished();
	float getCompletion();
	void runTask();

	sf::Thread thread;
	bool finished;
	sf::Clock elapsed_time;
	sf::Mutex mutex;
};

