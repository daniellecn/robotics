/*
 * WaypointManager.h
 *
 *  Created on: Jun 14, 2015
 *      Author: colman
 */

#ifndef WAYPOINTMANAGER_H_
#define WAYPOINTMANAGER_H_

#include <vector>
#include "Location.h"
using namespace std;

class WaypointManager {
	static const float WAYPOINT_REACH_RADIUS = 1;

	vector <Location> _waypointPool;
public:
	WaypointManager();
	virtual ~WaypointManager();
};

#endif /* WAYPOINTMANAGER_H_ */
