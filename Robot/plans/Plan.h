/*
 * Plan.h
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#ifndef PLAN_H_
#define PLAN_H_

#include "../behaviors/Behavior.h"
#include "../robot/Robot.h"

class Plan {

protected:
	Behavior** 	_behArr;
	Behavior* 	_start;
	Robot* 		_robot;

public:
	Plan(Robot* robot);
	virtual Behavior* getStartPoint() = 0;
	virtual ~Plan();
};

#endif /* PLAN_H_ */
