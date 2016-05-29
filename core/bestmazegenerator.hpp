#ifndef BESTMAZEGENERATOR_HPP
#define BESTMAZEGENERATOR_HPP
#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include <vector>


class TheBestMaze : public MazeGenerator
{

public:

	virtual void generateMaze(Maze& maze);	

	int random_num(int low, int high);
	void initialize_visited(Maze& maze);
	void view_visited(Maze& maze);
	void create_tunnel(Maze& maze, int y, int x);
	bool valid_cell(Maze& maze, int y, int x);

private:

	std::vector<std::vector<bool>> Visited;

};


#endif //BESTMAZEGENERATOR_HPP//