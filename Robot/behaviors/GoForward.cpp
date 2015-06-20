/*
 * GoForward.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: colman
 */

#include "GoForward.h"

GoForward::GoForward(Robot* robot):Behavior(robot) {
}

bool GoForward::startCondition()
{
	if(_robot->isForwardFree() )
		return true;
	else
		return false;
}

bool GoForward::stopCondition()
{
	if(!_robot->isForwardFree())
				return true;
			else
				return false;
}

void GoForward::action()
{
	_robot->setSpeed(0.4, 0.0);
}

GoForward::~GoForward() {
}
