#ifndef BESTMAZEGENERATOR_CPP
#define BESTMAZEGENERATOR_CPP

#include "bestmazegenerator.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include "Maze.hpp"
#include <iostream>
#include <algorithm>

ICS46_DYNAMIC_FACTORY_REGISTER(
	MazeGenerator, TheBestMaze, "The Best Maze Generator");


void TheBestMaze::generateMaze(Maze & maze)
{
	maze.addAllWalls();

	initialize_visited(maze);
	int y_coord= random_num(0, maze.getHeight()-1);
	int x_coord= random_num(0, maze.getWidth()-1);

	create_tunnel(maze, y_coord, x_coord);
}



int TheBestMaze::random_num(int low, int high)
{
	return rand()%(high-low+1) + low;
}

void TheBestMaze::initialize_visited(Maze & maze)
{
	Visited.resize(maze.getHeight());

	for (int i=0; i < maze.getHeight(); ++i)
	{
		Visited[i].resize(maze.getWidth());
	}
	for (int y= 0; y < maze.getHeight();  y++ )
	{
		for (int x=0; x < maze.getWidth(); x++)
		{
			Visited[y][x]= false;
		}
	}
}

void TheBestMaze::view_visited(Maze & maze)
{
	for (int y= 0; y < maze.getHeight();  y++ )
	{
		for (int x=0; x < maze.getWidth(); x++)
		{
			std::cout << Visited[y][x] << " ";
		}
		std::cout << std::endl;
	}

}

bool TheBestMaze::valid_cell(Maze& maze, int y, int x)
{
	if (!(y >= 0 && y < maze.getHeight() && x >= 0 && x < maze.getWidth()))
	{
		return false;
	}
	else if (Visited[y][x])
	{
		return false;
	}
	else
		return true;
};



void TheBestMaze::create_tunnel(Maze& maze, int y, int x)
{
	//Check if everything is visisted

	bool finished = true;
	for (int y= 0; y < maze.getHeight();  y++ )
	{
		for (int x=0; x < maze.getWidth(); x++)
		{
			if (!(Visited[y][x]))
				finished = false;
		}
	}
	if (finished == true)
		return;
	Visited[y][x] = true;
	//Create list of directions
	std::vector<Direction> direction_list= {Direction::up, Direction::left, Direction::right, Direction::down};
	std::random_shuffle(direction_list.begin(), direction_list.end());
	for (int i=0; i < 4; i++)
	{
		Direction direction= direction_list[i];

		if (direction == Direction::up)
		{
			int new_y= y- 1;
			if (valid_cell(maze, new_y, x))
			{
				maze.removeWall(x, y, Direction::up);
				create_tunnel(maze, new_y, x);
			}
		}
		else if (direction == Direction::left)
		{
			int new_x= x -1;
			if (valid_cell(maze, y, new_x))
			{
				maze.removeWall(x, y, Direction::left);
				create_tunnel(maze, y, new_x);
			}
		}
		else if (direction == Direction::right)
		{
			int new_x = x + 1;
			if (valid_cell(maze, y, new_x))
			{
				maze.removeWall(x,y, Direction::right);
				create_tunnel(maze, y, new_x);
			}
		}
		else if (direction == Direction::down)
		{
			int new_y= y+ 1;
			if (valid_cell(maze, new_y, x))
			{
				maze.removeWall(x,y, Direction::down);
				create_tunnel(maze, new_y, x);
			}
		}
	}

	return;
};
#endif //BESTMAZEGENERATOR_HPP//