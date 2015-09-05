#pragma once
#include "serviceLocator.h"
class entity
{
public:
	entity();
	virtual void update();
	virtual void eventUpdate(SDL_Event nextEvent);
	virtual void draw();
	~entity();
};

