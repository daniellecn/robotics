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
using namespace std;

class WaypointManager {
private:
	static const float WAYPOINT_REACH_RADIUS = 1;

	vector <location> _wayPointPool;

	void setWayPointPool(vector <wayPoint> wayPoints, PathPlanner* pathP);
	void setWayPoint(location point, cellGrid** grid);
public:
	WaypointManager(vector <wayPoint> wayPoints, PathPlanner* pathP);
	vector <location> getWayPointPool();
	virtual ~WaypointManager();
};

#endif /* WAYPOINTMANAGER_H_ */
