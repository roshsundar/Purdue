#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "solver.h"
#include "path.h"
#include "mazehelper.h"

char * solveMaze(Maze * m) {
    //An obvious upper bound on the size of the solution path is the number
    //of squares in the maze + 1 (to account for the '\0'). You could make
    //this a tighter bound by accounting for how many walls there are, but
    //this approach is good enough!
	char * retval = malloc(sizeof(char) * ((m->width * m->height) + 1));

	MazePos mp = {.xpos = m->start.xpos, .ypos = m->start.ypos};
	if (!depthFirstSolve(m, mp, retval, 0)) {
		fprintf(stderr, "No solution found!\n");
	} else {
		printf("Solution found: %s\n", retval);
	}
	
	return retval;
}

bool depthFirstSolve(Maze * m, MazePos curpos, char * path, int step) 
{
	if (!squareOK(curpos, m))
	{
		return false;
	}

	if (atEnd(curpos, m))
	{
		path[step] = '\0';
		return true;
	}
	
	m->maze[curpos.ypos][curpos.xpos].visited = true;

	MazePos pos;

	pos.xpos = curpos.xpos;
	pos.ypos = curpos.ypos - 1;

	if (depthFirstSolve(m, pos, path, step + 1))
	{
		path[step] = 'n';
		return true;
	}

	pos.xpos = curpos.xpos;
	pos.ypos = curpos.ypos + 1;
	if (depthFirstSolve(m, pos, path, step + 1))
	{
		path[step] = 's';
		return true;
	}

	pos.xpos = curpos.xpos + 1;
	pos.ypos = curpos.ypos;
	if (depthFirstSolve(m, pos, path, step + 1))
	{
		path[step] = 'e';
		return true;
	}

	pos.xpos = curpos.xpos - 1;
	pos.ypos = curpos.ypos;
	if (depthFirstSolve(m, pos, path, step + 1))
	{
		path[step] = 'w';
		return true;
	}

	path[step] = '\0';
	return false;
}