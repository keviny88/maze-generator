#ifndef BESTMAZESOLVER_HPP
#define BESTMAZESOLVER_HPP
#include "MazeSolver.hpp"
#include "Maze.hpp"
#include <vector>


class TheBestMazeSolver : public MazeSolver
{

public:

	virtual void solveMaze(const Maze & maze, MazeSolution& mazeSolution);

	void initialize_visited(const Maze& maze, MazeSolution & mazeSolution);
	void move_direction(const Maze& maze, MazeSolution & mazeSolution, int y, int x);
	bool valid_direction(const Maze& maze, MazeSolution & mazeSolution, int y, int x);

private:

	std::vector<std::vector<bool>> Solver_Visited;

};


#endif //BESTMAZESOLVER_HPP//