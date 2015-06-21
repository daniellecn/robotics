/*
 * PathPlanner.h
 *
 *  Created on: Jun 16, 2015
 *      Author: colman
 */

#ifndef PATHPLANNER_H_
#define PATHPLANNER_H_

#include "Map.h"
#include <list>
using namespace std;

struct location{
	int x;
	int y;
};

struct Acell{
	int g;
	int f;
	location currLoc;
};

enum DIR{
	UP = 0,
	LEFT,
	DOWN,
	RIGHT,
};

//namespace std {

class PathPlanner {
private:
	const location DIR_VEC[4] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

	Map* _map;
	Acell _start;
	Acell _goal;
	cellGrid **_grid;
	int _cost = 1;
	Acell calcCell(DIR dir, Acell currCell);
	bool isExistListByLoc(list<Acell>::iterator it1, list<Acell>::iterator it2, location loc);
	void checkGValue(Map* map);
	vector <location> plan();
	void calcHeuristicFunction(Map* map);

public:
	PathPlanner(Map* map, int xStart, int yStart, int xGoal, int yGoal);
	virtual ~PathPlanner();
	void search(Map* map);

};

//} /* namespace std */

#endif /* PATHPLANNER_H_ */
