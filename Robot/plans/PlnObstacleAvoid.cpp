/*
 * PlnObstacleAvoid.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "PlnObstacleAvoid.h"


PlnObstacleAvoid::PlnObstacleAvoid(Robot* robot):Plan(robot) {
	//Creating Behaviors

	//Creating behaviors
	_behArr = new Behavior*[4];
	_behArr[0] = new GoForward(_robot);
	_behArr[1] = new TurnRight(_robot);
	_behArr[2] = new TurnLeft(_robot);
	_behArr[3] = new TurnAround(_robot);

	//Connecting Behaviors
	_behArr[0]->addNext(_behArr[1]);
	_behArr[0]->addNext(_behArr[2]);
	_behArr[0]->addNext(_behArr[3]);
	_behArr[1]->addNext(_behArr[0]);
	_behArr[2]->addNext(_behArr[0]);
	_behArr[3]->addNext(_behArr[0]);

	_start = _behArr[0];
}

PlnObstacleAvoid::~PlnObstacleAvoid() {
	// TODO Auto-generated destructor stub
	for(int i=0;i<3;i++)
		delete _behArr[i];
}

Behavior* PlnObstacleAvoid::getStartPoint() {
	return _start;
}
