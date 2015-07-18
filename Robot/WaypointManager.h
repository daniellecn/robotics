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
#include "localization/ParticleManager.h"
#include "Robot.h"
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

class WaypointManager {
private:
	static const float REACH_RADIUS = 0.20;

	vector <locationF> 	_wayPointPool;
	int 				_targetIndex;
	locationF			_target;
	Robot*	 			_robot;

	void setWayPointPool(vector <wayPoint> wayPoints, PathPlanner* pathP);

	double distanceBetween(locationF a, locationF b);
	float  angleBetween(locationF a, locationF b);
public:
	WaypointManager(PathPlanner* pathP, Robot* robot);
	virtual ~WaypointManager();

	int	getTargetIndex();
	vector <locationF> getWayPointPool();
	bool 	isLastWaypoint();
	bool 	isWaypointReached(Position avgLocation);
	locationF 	switchToNextWaypoint();
	void 	turnToWaypoint(Position avgLocation,ParticleManager* pm,Map* map);
};

#endif /* WAYPOINTMANAGER_H_ */
