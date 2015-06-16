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

namespace PlayerCc {

class WaypointManager {
	static const int WAYPOINT_REACH_RADIUS = 5;

	vector <Location> _waypointPool;
public:
	WaypointManager();
	virtual ~WaypointManager();
};

} /* namespace PlayerCc */

#endif /* WAYPOINTMANAGER_H_ */
