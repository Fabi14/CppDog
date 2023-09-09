#include "Level.h"
#include <vector>
#include <ranges>

int main()
{
	Dog spencer;

	//Level 01
	spencer.run(Direction::down);
	spencer.run(Direction::down);

	spencer.run(Direction::right);
	spencer.run(Direction::right);
	spencer.run(Direction::right);
	spencer.run(Direction::right);

	//Level 02
	std::vector<Direction> vecDirections{ 
		Direction::up,
		Direction::right,
		Direction::up,
		Direction::right,
		Direction::up,
		Direction::up,
		Direction::right,
		Direction::right,
		Direction::down
	};
	for (auto direction : vecDirections)
	{
		spencer.run(direction);
	}

	//Level 03
	for (auto direction : std::views::repeat(Direction::up) | std::views::take(5))
	{
		spencer.run(direction);
	}
	for (auto direction : std::views::repeat(Direction::left) | std::views::take(9))
	{
		spencer.run(direction);
	}
	for (auto direction : std::views::repeat(Direction::down) | std::views::take(3))
	{
		spencer.run(direction);
	}

	return 0;
}

