#pragma once

//Controls:
// Restart Level: SPACE
// Exit: ESCAPE
// Help: h

enum class Direction
{
	left,
	right,
	up,
	down
};

class Dog {
public:
	~Dog();
	void run(Direction direction);
};



enum class Level
{
	level_01_functions,
	level_02_loops,
};

void selectLevel(Level level);