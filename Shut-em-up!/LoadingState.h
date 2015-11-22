#pragma once
#include "SFML\Graphics.hpp"
#include "State.h"
#include "ParallelTask.h"

struct LoadingState: public State
{
	LoadingState(StateStack& state, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

	void setCompletion(float percent);

	sf::Text				loading_text;	
	sf::RectangleShape		progress_background;
	sf::RectangleShape		progress_bar;

	ParallelTask			loading_task;
};

