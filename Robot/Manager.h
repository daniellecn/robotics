/*
 * Manager.h
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#ifndef MANAGER_H_
#define MANAGER_H_

#include "robot/Robot.h"
#include "plans/Plan.h"
#include "localization/ParticleManager.h"
#include "orientation/PathPlanner.h"
#include "orientation/WaypointManager.h"
#include <vector>

class Manager {
	Behavior* 			_curr;
	Robot* 				_robot;
	ParticleManager* 	_pm;
	Map*			 	_map;
	Plan*			 	_plan;
	WaypointManager* 	_wm;
	PathPlanner*		_path;

public:
	Manager(Robot* robot, Map* map, Plan* plan, PathPlanner* pathPlan);
	void run();
	virtual ~Manager();
};

#endif /* MANAGER_H_ */
