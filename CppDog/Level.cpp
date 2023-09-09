#include "Level.h"
#include "App.h"

App& getAppInstance()
{
	static App app;
	return app;
}


void selectLevel(Level level)
{
}

Dog::~Dog()
{
	App& demo = getAppInstance();
	if (demo.Construct(1920, 1080, 1, 1))
		demo.Start();
}

void Dog::run(Direction direction)
{
	App& demo = getAppInstance();
	demo.runDog(direction);
}
