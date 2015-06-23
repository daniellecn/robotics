/*
 * Manager.h
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#ifndef MANAGER_H_
#define MANAGER_H_
#include "plans/Plan.h"
#include "localization/ParticleManager.h"
#include "Robot.h"
#include <vector>

using namespace std;
class Manager {
	Behavior* _curr;
	Robot* _robot;
	ParticleManager* _pm;
	Map*			 _map;
	Plan*			 _plan;
public:
	Manager(Robot* robot, Map* map, Plan* plan);
	void run();
	virtual ~Manager();
};

#endif /* MANAGER_H_ */
