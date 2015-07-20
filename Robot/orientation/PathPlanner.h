/*
 * PathPlanner.h
 *
 *  Created on: Jun 16, 2015
 *      Author: colman
 */

#ifndef PATHPLANNER_H_
#define PATHPLANNER_H_

#include "../GeneralService.h"
#include "Map.h"
#include <list>
using namespace std;

enum DIR{
	UP = 0,
	UP_RIGHT,
	RIGHT,
	RIGHT_DOWN,
	DOWN,
	DOWN_LEFT,
	LEFT,
	LEFT_UP,
};

class PathPlanner {
private:
	const location DIR_VEC[8] = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1,1}, {-1, 0}, {-1, -1}};

	Map* _map;
	Acell _start;
	Acell _goal;
	cellGrid **_grid;
	vector <wayPoint> _wayPoints;

	void setStartIndex(int y, int x, int g, int f);
	void setGoalIndex(int y, int x, int g, int f);
	void setGrid(cellGrid** grid);
	void setMap(Map* map);
	void setWayPoint(wayPoint wayPoint);

	void calcHeuristicFunction();
	void calcPriorities();

	bool isExistListByLoc(list<Acell>::iterator it1, list<Acell>::iterator it2, location loc);
	void plan();


public:
	PathPlanner(Map* map, int xStart, int yStart, int xGoal, int yGoal);
	virtual ~PathPlanner();

	Acell getStartIndex();
	Acell getGoalIndex();
	cellGrid** getGrid();
	Map* getMap();
	vector <wayPoint> getWayPoints();

	void search();


};

#endif /* PATHPLANNER_H_ */
