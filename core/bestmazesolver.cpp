#ifndef BESTMAZESOLVER_CPP
#define BESTMAZESOLVER_CPP

#include "MazeSolution.hpp"
#include "bestmazesolver.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include "Maze.hpp"
#include <iostream>

ICS46_DYNAMIC_FACTORY_REGISTER(
	MazeSolver, TheBestMazeSolver, "The Best Maze Solver");

void TheBestMazeSolver::initialize_visited(const Maze & maze, MazeSolution& mazeSolution)
{
	Solver_Visited.resize(mazeSolution.getHeight());

	for (int i=0; i < maze.getHeight(); ++i)
	{
		Solver_Visited[i].resize(mazeSolution.getWidth());
	}
	for (int y= 0; y < mazeSolution.getHeight();  y++ )
	{
		for (int x=0; x < mazeSolution.getWidth(); x++)
		{
			Solver_Visited[y][x]= false;
		}
	}
}
void TheBestMazeSolver::solveMaze(const Maze & maze, MazeSolution& mazeSolution)
{
	initialize_visited(maze, mazeSolution);
	int y_coord= 0; int x_coord= 0;

	move_direction(maze, mazeSolution, y_coord, x_coord);

}

bool TheBestMazeSolver::valid_direction(const Maze& maze, MazeSolution& mazeSolution, int y, int x)
{
	if (!(y >= 0 && y < mazeSolution.getHeight() && x >= 0 && x < mazeSolution.getWidth()))
	{
		return false;
	}
	else if (Solver_Visited[y][x])
	{
		return false;
	}
	else
		return true;
};



void TheBestMazeSolver::move_direction(const Maze& maze, MazeSolution& mazeSolution, int y, int x)
{
	//Check if everything is visisted

	if (mazeSolution.isComplete())
		return;

	Solver_Visited[y][x] = true;

	//Create list of directions
	std::vector<Direction> direction_list= {Direction::up, Direction::left, Direction::right, Direction::down};
	std::random_shuffle(direction_list.begin(), direction_list.end());

	for (int i=0; i < 4; i++)
	{
		Direction direction= direction_list[i];

		if (mazeSolution.isComplete())
				return;

		if (direction == Direction::up)
		{
			int new_y= y- 1;
			if (valid_direction(maze, mazeSolution, new_y, x) && !(maze.wallExists(x, y, Direction::up)))
			{
				mazeSolution.extend(Direction::up);
				if (mazeSolution.isComplete())
					return;
				move_direction(maze, mazeSolution, new_y, x);
			}
		}
		else if (direction == Direction::left)
		{
			int new_x= x -1;
			if (valid_direction(maze, mazeSolution, y, new_x) && !(maze.wallExists(x, y, Direction::left)))
			{
				mazeSolution.extend(Direction::left);
				if (mazeSolution.isComplete())
					return;
				move_direction(maze, mazeSolution, y, new_x);
			}
		}
		else if (direction == Direction::right)
		{
			int new_x = x + 1;
			if (valid_direction(maze, mazeSolution,  y, new_x) && !(maze.wallExists(x, y, Direction::right)))
			{
				mazeSolution.extend(Direction::right);
				if (mazeSolution.isComplete())
					return;
				move_direction(maze, mazeSolution, y, new_x);
			}
		}
		else if (direction == Direction::down)
		{
			int new_y= y+ 1;
			if (valid_direction(maze, mazeSolution, new_y, x) && !(maze.wallExists(x, y, Direction::down)))
			{
				mazeSolution.extend(Direction::down);
				if (mazeSolution.isComplete())
					return;
				move_direction(maze, mazeSolution, new_y, x);
			}
		}
	}
	if (mazeSolution.isComplete())
		return;

	mazeSolution.backUp();
};


#endif //BESTMAZESOLVER_CPP//