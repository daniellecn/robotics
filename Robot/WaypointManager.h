/*
 * WaypointManager.h
 *
 *  Created on: Jun 14, 2015
 *      Author: colman
 */

#ifndef WAYPOINTMANAGER_H_
#define WAYPOINTMANAGER_H_

#include <vector>
#include "GeneralService.h"
#include "PathPlanner.h"
#include "Robot.h"
#include <vector>
#include <math.h>
using namespace std;

class WaypointManager {
private:
	static const float REACH_RADIUS = 0.35;

	vector <location> _wayPointPool;
	int 				_targetIndex;
	location			_target;
	Robot*	 			_robot;

	void setWayPointPool(vector <wayPoint> wayPoints, PathPlanner* pathP);
	void setWayPoint(location point, cellGrid** grid);

	double distanceBetween(location a, location b);
	float  angleBetween(location a, location b);
public:
	WaypointManager(PathPlanner* pathP, Robot* robot);
	virtual ~WaypointManager();

	vector <location> getWayPointPool();
	bool 	isEndReached(Position avgLocation);
	bool 	isWaypointReached(Position avgLocation);
	float 	getAngleToWaypoint();
	void 	goToWaypoint(Position avgLocation);
	void 	getNextWaypoint();
};

#endif /* WAYPOINTMANAGER_H_ */
