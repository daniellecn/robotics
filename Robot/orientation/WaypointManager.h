/*
 * WaypointManager.h
 *
 *  Created on: Jun 14, 2015
 *      Author: colman
 */

#ifndef WAYPOINTMANAGER_H_
#define WAYPOINTMANAGER_H_

#include "../GeneralService.h"
#include "PathPlanner.h"
#include "../robot/Robot.h"

#include <vector>
#include <algorithm>

class WaypointManager {
private:

	vector <locationF> 	_wayPointPool;
	int 				_targetIndex;
	locationF			_target;
	Robot*	 			_robot;

	void setWayPointPool(vector <wayPoint> wayPoints, PathPlanner* pathP);
	double distanceBetween(locationF a, locationF b);

public:
	WaypointManager(PathPlanner* pathP, Robot* robot);
	virtual ~WaypointManager();

	int					getTargetIndex();
	vector <locationF> 	getWayPointPool();
	locationF 			switchToNextWaypoint();
	bool 				isLastWaypoint();
	bool 				isWaypointReached(position avgLocation);
	bool 				turnToWaypoint(position avgLocation);
};

#endif /* WAYPOINTMANAGER_H_ */
