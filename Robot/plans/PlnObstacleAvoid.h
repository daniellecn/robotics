/*
 * PlnObstacleAvoid.h
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#ifndef PLNOBSTACLEAVOID_H_
#define PLNOBSTACLEAVOID_H_

#include "Plan.h"

#include "../behaviors/TurnRight.h"
#include "../behaviors/TurnLeft.h"
#include "../behaviors/GoForward.h"
#include "../behaviors/TurnAround.h"

class PlnObstacleAvoid: public Plan {
public:
	PlnObstacleAvoid(Robot* robot);
	Behavior* getStartPoint();
	virtual ~PlnObstacleAvoid();
};

#endif /* PLNOBSTACLEAVOID_H_ */
