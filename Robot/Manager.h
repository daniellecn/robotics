/*
 * Manager.h
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#ifndef MANAGER_H_
#define MANAGER_H_
#include "plans/PlnObstacleAvoid.h"
#include "behaviors/TurnLeft.h"
#include "behaviors/TurnRight.h"
#include "Robot.h"
#include "localization/ParticleManager.h"
#include <vector>

using namespace std;
class Manager {
	Behavior* _curr;
	Behavior* _beh[3];
	Robot* _robot;
	ParticleManager* _pm;
	Map*			 _map;
public:
	Manager(Robot* robot, Map* map);
	void run();
	virtual ~Manager();
};

#endif /* MANAGER_H_ */
